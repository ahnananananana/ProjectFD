// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"

UGameplayAbilityBase::UGameplayAbilityBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UGameplayAbilityBase* FAbilityInfo::CreateInstance(UObject* _pOuter) const
{
	UGameplayAbilityBase* pInstance = NewObject<UGameplayAbilityBase>(_pOuter, Ability);
	pInstance->Init(*this);
	return pInstance;
}