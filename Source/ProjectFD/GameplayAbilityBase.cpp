// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"

UGameplayAbilityBase::UGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* _pActorInfo, const FGameplayAbilitySpec& _Spec)
{
	Super::OnGiveAbility(_pActorInfo, _Spec);
	m_Handle = _Spec.Handle;
}

UGameplayAbilityBase* FAbilityInfo::CreateInstance(UObject* _pOuter) const
{
	UGameplayAbilityBase* pInstance = NewObject<UGameplayAbilityBase>(_pOuter, Ability);
	pInstance->Init(*this);
	return pInstance;
}