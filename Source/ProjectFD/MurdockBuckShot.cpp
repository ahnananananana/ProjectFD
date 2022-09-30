// Fill out your copyright notice in the Description page of Project Settings.


#include "MurdockBuckShot.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

void UMurdockBuckShot::Init(const FAbilityInfo& _Info)
{
	m_pMontage = _Info.Montages[0];
	m_pShotParticle = _Info.Particles[0];
	m_pHitParticle = _Info.Particles[1];
}

bool UMurdockBuckShot::CanActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayTagContainer* _pSourceTags, const FGameplayTagContainer* _pTargetTags, OUT FGameplayTagContainer* _pOptionalRelevantTags) const
{
	ACharacter* pCharacter = Cast<ACharacter>(GetOwningActorFromActorInfo());
	return pCharacter->GetCurrentMontage() != m_pMontage;
}

void UMurdockBuckShot::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	Super::ActivateAbility(_Handle, _pActorInfo, _ActivationInfo, _pTriggerEventData);

	if (ACharacter* pCharacter = Cast<ACharacter>(_pActorInfo->OwnerActor))
	{
		pCharacter->PlayAnimMontage(m_pMontage);
	}
}

void UMurdockBuckShot::OnNotify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pShotParticle, _pMeshComp->GetSocketTransform(m_strMuzzleName));

}
