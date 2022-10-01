// Fill out your copyright notice in the Description page of Project Settings.


#include "MurdockGunShield.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void UMurdockGunShield::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);

	_pActorInfo->SkeletalMeshComponent->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &UMurdockGunShield::OnMontageEnded);
}

void UMurdockGunShield::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	Super::ActivateAbility(_Handle, _pActorInfo, _ActivationInfo, _pTriggerEventData);

	ACharacter* pOwner = Cast<ACharacter>(_pActorInfo->OwnerActor);
	pOwner->PlayAnimMontage(m_pActivationMontage);

	FTransform trans = pOwner->GetMesh()->GetSocketTransform(m_strShieldSocketName);
	m_pCurActivationParticleComp = UGameplayStatics::SpawnEmitterAttached(m_pShieldActivationParticle, pOwner->GetMesh(), m_strShieldSocketName);
}

bool UMurdockGunShield::CanBeCanceled() const
{
	ACharacter* pOwner = Cast<ACharacter>(GetOwningActorFromActorInfo());
	m_bCancelRequested = true;
	return pOwner->GetCurrentMontage() == m_pLoopMontage;
}

void UMurdockGunShield::CancelAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, bool _bReplicateCancelAbility)
{
	if (CanBeCanceled())
	{
		ACharacter* pOwner = Cast<ACharacter>(_pActorInfo->OwnerActor);
		pOwner->PlayAnimMontage(m_pDeactivationMontage);

		FTransform trans = pOwner->GetMesh()->GetSocketTransform(m_strShieldSocketName);
		//TODO: Attach가 되지 않는다. 왜?
		UGameplayStatics::SpawnEmitterAttached(m_pShieldDeactivationParticle, pOwner->GetMesh(), m_strShieldSocketName);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pShieldExplodeParticle, trans);
		m_pCurActivationParticleComp->DestroyComponent();
	}
}

void UMurdockGunShield::EndAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, bool _bReplicateEndAbility, bool _bWasCancelled)
{
	Super::EndAbility(_Handle, _pActorInfo, _ActivationInfo, _bReplicateEndAbility, _bWasCancelled);
	m_bCancelRequested = false;
}

void UMurdockGunShield::OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted)
{
	if (_pMontage == m_pActivationMontage)
	{
		ACharacter* pOwner = Cast<ACharacter>(GetOwningActorFromActorInfo());
		if (m_bCancelRequested)
		{
			pOwner->PlayAnimMontage(m_pDeactivationMontage);

			FTransform trans = pOwner->GetMesh()->GetSocketTransform(m_strShieldSocketName);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pShieldExplodeParticle, trans);
			UGameplayStatics::SpawnEmitterAttached(m_pShieldDeactivationParticle, pOwner->GetMesh(), m_strShieldSocketName);
			m_pCurActivationParticleComp->DestroyComponent();
		}
		else
		{
			pOwner->PlayAnimMontage(m_pLoopMontage);
		}
	}
	else if (_pMontage == m_pDeactivationMontage)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}
}