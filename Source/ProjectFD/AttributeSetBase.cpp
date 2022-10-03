// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"

UAttributeSetBase::UAttributeSetBase()
{
}

void UAttributeSetBase::Init(const FDataTableRowHandle& _DataHandle)
{
	FCharacterData* pData = _DataHandle.GetRow<FCharacterData>("");

	if (!pData)
	{
		UE_LOG(LogScript, Error, TEXT("Wrong Data Handle %s"), *_DataHandle.RowName.ToString());
		return;
	}

	OnInit(*pData);
}

void UAttributeSetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& _AffectedAttribute, const FGameplayAttributeData& _MaxAttribute, float _fNewMaxValue, const FGameplayAttribute& _AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = _MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, _fNewMaxValue) && AbilityComp)
	{
		const float CurrentValue = _AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * _fNewMaxValue / CurrentMaxValue) - CurrentValue : _fNewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(_AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

