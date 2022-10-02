// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"
#include "CustomStruct.h"

UGameCharacterAttributeSet::UGameCharacterAttributeSet()
{
}

void UGameCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& _Attribute, float& _fNewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(_Attribute, _fNewValue);

	OnAttributeValueChanged.Broadcast(_Attribute, _fNewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	if (_Attribute == GetMaxHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, _fNewValue, GetHealthAttribute());
	}
	else if (_Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, _fNewValue, GetManaAttribute());
	}
}

void UGameCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGameCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGameCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGameCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGameCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGameCharacterAttributeSet, AttackDamage, COND_None, REPNOTIFY_Always);
}

void UGameCharacterAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UGameCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGameCharacterAttributeSet, Health, _oldValue);
}

void UGameCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGameCharacterAttributeSet, MaxHealth, _oldValue);
}

void UGameCharacterAttributeSet::OnRep_Mana(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGameCharacterAttributeSet, Mana, _oldValue);
}

void UGameCharacterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGameCharacterAttributeSet, MaxMana, _oldValue);
}

void UGameCharacterAttributeSet::OnRep_AttackDamage(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGameCharacterAttributeSet, AttackDamage, _oldValue);
}

void UGameCharacterAttributeSet::Init(FDataTableRowHandle& _handle)
{
	FCharacterData* pData = _handle.GetRow<FCharacterData>("");

	if (!pData)
	{
		UE_LOG(LogScript, Error, TEXT("Wrong Data Handle %s"), *_handle.RowName.ToString());
		return;
	}

	SetMaxHealth(pData->MaxHealth);
	SetHealth(pData->Health);
	SetMaxMana(pData->MaxMana);
	SetMana(pData->Mana);
	SetAttackDamage(pData->AttackDamage);
}