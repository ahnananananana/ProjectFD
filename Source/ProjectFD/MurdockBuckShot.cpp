#include "MurdockBuckShot.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameBaseCharacter.h"

void UMurdockBuckShot::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);
	_pActorInfo->SkeletalMeshComponent->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &UMurdockBuckShot::OnMontageEnded);
}

void UMurdockBuckShot::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	Super::ActivateAbility(_Handle, _pActorInfo, _ActivationInfo, _pTriggerEventData);

	if (ACharacter* pCharacter = Cast<ACharacter>(_pActorInfo->OwnerActor))
	{
		pCharacter->PlayAnimMontage(m_pMontage);
		CommitAbilityCooldown(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
	}
}

void UMurdockBuckShot::OnMontageEnded(UAnimMontage* _pMontage, bool _bInterrupted)
{
	if (_pMontage == m_pMontage)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
	}
}

void UMurdockBuckShot::OnNotify(const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference)
{
	FVector vLoc = _pMeshComp->GetSocketLocation(m_strMuzzleName);
	FVector vDir = (Cast<AGameBaseCharacter>(GetOwningActorFromActorInfo())->GetAimPoint() - vLoc);

	FTransform trans(vDir.ToOrientationRotator(), vLoc);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pShotParticle, trans);
	//TODO: 스폰을 안하고 안에 Primitive Component 정보만 빼올 수 없나
	AActor* pShapeActor = GetWorld()->SpawnActor<AActor>(m_pShotOverlapShape, trans);
	UPrimitiveComponent* pShape = pShapeActor->FindComponentByClass<UPrimitiveComponent>();

	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> ignore{GetOwningActorFromActorInfo()};
	TArray<AActor*> result;
	if (UKismetSystemLibrary::ComponentOverlapActors(pShape, pShape->GetComponentTransform(), traceObjectTypes, nullptr, ignore, result))
	{
		for (AActor* pTarget : result)
		{
			if (IAbilitySystemInterface* pASInter = Cast<IAbilitySystemInterface>(pTarget))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), m_pHitParticle, pTarget->GetActorTransform());
				FGameplayEffectContextHandle context;
				pASInter->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(m_pDamageEffect.GetDefaultObject(), 1, context);
			}
		}
	}

	GetWorld()->DestroyActor(pShapeActor);
}
