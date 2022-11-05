// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectileAbility.h"
#include "GameBaseCharacter.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

void UShootProjectileAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);
	_pActorInfo->SkeletalMeshComponent->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &UShootProjectileAbility::OnMontageEnded);
}

void UShootProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	Super::ActivateAbility(_Handle, _pActorInfo, _ActivationInfo, _pTriggerEventData);

	UE_LOG(LogTemp, Log, TEXT("ActivateAbility %d"), GetWorld()->IsServer());

	AGameBaseCharacter* pOwner = Cast<AGameBaseCharacter>(GetOwningActorFromActorInfo());
	pOwner->PlayAnimMontage(m_pShootMontage);

	CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);

	const FTransform& muzzleTrans = pOwner->GetMesh()->GetSocketTransform(m_strMuzzleSocketName);
	const FVector& vDir = pOwner->GetAimPoint() - muzzleTrans.GetLocation();

	FTransform trans(vDir.ToOrientationRotator(), muzzleTrans.GetLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pShootParticleBP, trans);

	AProjectile* pProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(m_pProjectileBP, trans, nullptr, pOwner);
	pProjectile->SetEffectHandle(MakeOutgoingGameplayEffectSpec(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, m_pDamageEffectBP, 1.f));
	UGameplayStatics::FinishSpawningActor(pProjectile, trans);
}

void UShootProjectileAbility::OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}