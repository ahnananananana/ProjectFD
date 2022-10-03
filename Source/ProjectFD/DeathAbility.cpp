// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathAbility.h"
#include "AbilitySystemComponent.h"
#include "GameBaseCharacter.h"
#include "Components/WidgetComponent.h"
#include "GameCharacterAttributeSet.h"

void UDeathAbility::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);

	_pActorInfo->AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UGameCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &UDeathAbility::OnHealthChanged);
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

void UDeathAbility::OnHealthChanged(const FOnAttributeChangeData& _ChangeData)
{
	if (_ChangeData.OldValue > 0.f && _ChangeData.NewValue <= 0.f)
	{
		GetAbilitySystemComponentFromActorInfo()->TryActivateAbility(GetCurrentAbilitySpecHandle());
		EndAbility(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, false, false);
	}
}