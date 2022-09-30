// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityBase.h"
#include "MurdockBuckShot.generated.h"

class UAnimMontage;
class UParticleSystem;

UCLASS()
class PROJECTFD_API UMurdockBuckShot : public UGameplayAbilityBase
{
	GENERATED_BODY()

	UAnimMontage* m_pMontage;
	UParticleSystem* m_pShotParticle, *m_pHitParticle;
	//TODO: �ܺο��� �޾ƿ;�? ���� �̸��� ���� ���?
	FName m_strMuzzleName = TEXT("Muzzle_03");

public:
	void Init(const FAbilityInfo& _Info) override;

	bool CanActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayTagContainer* _pSourceTags = nullptr, const FGameplayTagContainer* _pTargetTags = nullptr, OUT FGameplayTagContainer* _pOptionalRelevantTags = nullptr) const override;

protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData) override;
	void OnNotify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference) override;
};
