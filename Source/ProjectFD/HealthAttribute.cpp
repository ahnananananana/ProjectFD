// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttribute.h"

UHealthAttribute::UHealthAttribute()
{

}

void UHealthAttribute::PreAttributeChange(const FGameplayAttribute& _Attribute, float& _fNewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(_Attribute, _fNewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	if (_Attribute == GetMaxHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, _fNewValue, GetHealthAttribute());
	}
}

void UHealthAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttribute, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttribute, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttribute, HealthRegen, COND_None, REPNOTIFY_Always);
}

void UHealthAttribute::OnRep_Health(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttribute, Health, _oldValue);
}

void UHealthAttribute::OnRep_MaxHealth(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttribute, MaxHealth, _oldValue);
}

void UHealthAttribute::OnRep_HealthRegen(const FGameplayAttributeData& _oldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttribute, HealthRegen, _oldValue);
}

//TODO: string으로 검색해서 가져올 수는 없나
void UHealthAttribute::OnInit(const FCharacterData& _Data)
{
	SetMaxHealth(_Data.MaxHealth);
	SetHealth(_Data.Health);
	SetHealthRegen(_Data.HealthRegen);
}