// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityBase.h"
#include "DeathAbility.generated.h"

class UAnimMontage;

UCLASS()
class PROJECTFD_API UDeathAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, DisplayName = "Montages", meta = (AllowPrivateAccess))
	TArray<UAnimMontage*> m_arrDeadMontage;
	
public:
	void OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec) override;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData) override;

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnHealthChanged(float _fNewValue, float _fOldValue);
};
