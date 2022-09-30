// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathAbility.h"
#include "HealthComponent.h"
#include "AbilitySystemComponent.h"
#include "GameBaseCharacter.h"
#include "Components/WidgetComponent.h"

void UDeathAbility::Init(const FAbilityInfo& _Info)
{
	m_arrDeadMontage = _Info.Montages;
}

void UDeathAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);

	if (UHealthComponent* pHealthComp = Cast<UHealthComponent>(_pActorInfo->OwnerActor->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		pHealthComp->OnHealthChanged.AddDynamic(this, &UDeathAbility::OnHealthChanged);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No UHealthComponent!"));
	}
}

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle _Handle, const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilityActivationInfo _ActivationInfo, const FGameplayEventData* _pTriggerEventData)
{
	Super::ActivateAbility(_Handle, _pActorInfo, _ActivationInfo, _pTriggerEventData);

	if (AGameBaseCharacter* pCharacter = Cast<AGameBaseCharacter>(_pActorInfo->OwnerActor))
	{
		pCharacter->PlayAnimMontage(m_arrDeadMontage[0]);
		pCharacter->SetActorEnableCollision(false);
		pCharacter->AddGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("Dead")));
		pCharacter->FindComponentByClass<UWidgetComponent>()->SetVisibility(false);
	}
}

void UDeathAbility::OnHealthChanged(float _fNewValue, float _fOldValue)
{
	if (_fNewValue <= 0.f)
	{
		GetAbilitySystemComponentFromActorInfo()->TryActivateAbility(m_Handle);
	}
}