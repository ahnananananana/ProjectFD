// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathAbility.h"
#include "HealthComponent.h"
#include "AbilitySystemComponent.h"
#include "GameBaseCharacter.h"

void UDeathAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);

	if (UHealthComponent* pHealthComp = Cast<UHealthComponent>(_pActorInfo->OwnerActor->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		pHealthComp->OnAttributeChanged.AddUObject(this, &UDeathAbility::OnHealthChanged);
	}
	else
	{
		UE_LOG(LogScript, Warning, TEXT("No UHealthComponent!"));
	}
}

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	if (AGameBaseCharacter* pCharacter = Cast<AGameBaseCharacter>(_pActorInfo->OwnerActor))
	{
		pCharacter->PlayAnimMontage(pCharacter->GetCharacterData()->DeadMontages[0]);
		
	}
}

void UDeathAbility::OnHealthChanged(float _fNewValue, float _fOldValue)
{
	if (_fNewValue <= 0.f)
	{
		GetAbilitySystemComponentFromActorInfo()->TryActivateAbilityByClass(ThisClass::StaticClass());
	}
}