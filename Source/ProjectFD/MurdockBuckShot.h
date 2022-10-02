// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterAbility.h"
#include "MurdockBuckShot.generated.h"

class UAnimMontage;
class UParticleSystem;

UCLASS()
class PROJECTFD_API UMurdockBuckShot : public UPlayerCharacterAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, DisplayName = "Shoot Montage", meta = (AllowPrivateAccess))
	UAnimMontage* m_pMontage;
	UPROPERTY(EditAnywhere, DisplayName = "Shot Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pShotParticle;
	UPROPERTY(EditAnywhere, DisplayName = "Hit Particle", meta = (AllowPrivateAccess))
	UParticleSystem* m_pHitParticle;
	//TODO: 외부에서 받아와야? 소켓 이름의 변경 대비?
	UPROPERTY(EditAnywhere, DisplayName = "Muzzel Socket Name", meta = (AllowPrivateAccess))
	FName m_strMuzzleName = TEXT("Muzzle_03");
	UPROPERTY(EditAnywhere, DisplayName = "Damage Effect", meta = (AllowPrivateAccess))
	TSubclassOf<UGameplayEffect> m_pDamageEffect;
	UPROPERTY(EditAnywhere, DisplayName = "Shot Overlap Shape", meta = (AllowPrivateAccess))
	TSubclassOf<AActor> m_pShotOverlapShape;

public:
	void OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec) override;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData) override;
	void OnNotify(const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference) override;

private:
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted);
};
