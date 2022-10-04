// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterAbility.h"
#include "ShootProjectileAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFD_API UShootProjectileAbility : public UPlayerCharacterAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, DisplayName = "Shoot Montage", meta = (AllowPrivateAccess))
	UAnimMontage* m_pShootMontage;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Projectile", meta = (AllowPrivateAccess))
	TSubclassOf<AActor> m_pProjectileBP;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Shoot Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pShootParticleBP;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Damage Effect", meta = (AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> m_pDamageEffectBP;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Muzzel Socket Name", meta = (AllowPrivateAccess))
	FName m_strMuzzleSocketName;

public:
	void OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec) override;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData) override;

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted);
};
