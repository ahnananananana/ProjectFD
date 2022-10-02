// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterAbility.h"
#include "MurdockGunShield.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFD_API UMurdockGunShield : public UPlayerCharacterAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, DisplayName = "Activation Montage", meta = (AllowPrivateAccess))
	UAnimMontage* m_pActivationMontage;
	UPROPERTY(EditAnywhere, DisplayName = "Loop Montage", meta = (AllowPrivateAccess))
	UAnimMontage* m_pLoopMontage;
	UPROPERTY(EditAnywhere, DisplayName = "Deactivation Montage", meta = (AllowPrivateAccess))
	UAnimMontage* m_pDeactivationMontage;
	UPROPERTY(EditAnywhere, DisplayName = "Shield Activation Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pShieldActivationParticle;
	UPROPERTY(EditAnywhere, DisplayName = "Shield Deactivation Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pShieldDeactivationParticle;
	UPROPERTY(EditAnywhere, DisplayName = "Shield Explode Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pShieldExplodeParticle;
	UPROPERTY(EditAnywhere, DisplayName = "Shield Socket Name", meta = (AllowPrivateAccess))
	FName m_strShieldSocketName;
	UPROPERTY(EditAnywhere, DisplayName = "Shield Collider Actor", meta = (AllowPrivateAccess))
	TSubclassOf<AActor> m_pShieldColliderActor;

	UParticleSystemComponent* m_pCurActivationParticleComp;
	mutable bool m_bCancelRequested;

public:
	void OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec) override;
	void CancelAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, bool _bReplicateCancelAbility) override;
	//void EndAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, bool _bReplicateEndAbility, bool _bWasCancelled) override;
	bool CanBeCanceled() const override;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData) override;
	void EndAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, bool _bReplicateEndAbility, bool _bWasCancelled) override;

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted);
};
