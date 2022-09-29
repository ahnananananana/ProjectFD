// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"

UGameplayAbilityBase::UGameplayAbilityBase()
{

}

void UGameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);
}
