// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CustomEnums.h"
#include "GameplayAbilityBase.generated.h"

class UAnimMontage;
class UGameplayAbilityBase;
class UParticleSystem;

UCLASS(BlueprintType, Abstract)
class PROJECTFD_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbilityBase();

protected:
	virtual void OnNotify(const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference) {}

	friend struct FAbilityInfo;
	friend class UAbilitySystemComponentBase;
};