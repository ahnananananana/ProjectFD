// Copyright ahnananananana. All Rights Reserved.


#include "ParagonCharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"
#include "../CustomStruct.h"


//void UParagonCharacterAttributeSet::Init(FDataTableRowHandle& _handle)
//{
//	FCharacterData* pData = _handle.GetRow<FCharacterData>("");
//
//	if (!pData)
//	{
//		UE_LOG(LogScript, Error, TEXT("Wrong Data Handle %s"), *_handle.RowName.ToString());
//		return;
//	}
//
//	SetMaxHealth(pData->MaxHealth);
//	SetHealth(pData->Health);
//	SetMaxMana(pData->MaxMana);
//	SetMana(pData->Mana);
//	SetBasicAttackDamage(pData->AttackDamage);
//	//SetMoveSpeed(pData->AttackDamage);
//}

void UParagonCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, BasicAttackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, BasicAttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UParagonCharacterAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UParagonCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		//AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetHealthAttribute())
	{
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
	else if (Attribute == GetManaAttribute())
	{
	}
}