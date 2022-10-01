// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CustomEnums.h"
#include "GameplayAbilityBase.generated.h"

class UAnimMontage;
class UGameplayAbilityBase;
class UParticleSystem;

USTRUCT(BlueprintType)
struct FAbilityInfo 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Ability")
	TSubclassOf<UGameplayAbilityBase> Ability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Montages")
	TArray<UAnimMontage*> Montages;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Particles")
	TArray<UParticleSystem*> Particles;

	UGameplayAbilityBase* CreateInstance(UObject* _pOuter) const;
};

UCLASS(BlueprintType, Abstract)
class PROJECTFD_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	FGameplayAbilitySpecHandle m_Handle;

public:
	UGameplayAbilityBase();
	void OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec) override;

private:
	virtual void Init(const FAbilityInfo& _info) {}

protected:
	virtual void OnNotify(const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference) {}

	friend struct FAbilityInfo;
	friend class UAbilitySystemComponentBase;
};