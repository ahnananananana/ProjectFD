// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "CustomMacros.h"
#include "CustomStruct.h"
#include "Net/UnrealNetwork.h"
#include "AttributeSetBase.generated.h"


UCLASS(Abstract, BlueprintType)
class PROJECTFD_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSetBase();

	void Init(const FDataTableRowHandle& _DataHandle);

protected:
	virtual void OnInit(const FCharacterData& _Data) PURE_VIRTUAL(UAttributeSetBase::OnInit);

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& _AffectedAttribute, const FGameplayAttributeData& _MaxAttribute, float _fNewMaxValue, const FGameplayAttribute& _AffectedAttributeProperty);
};
