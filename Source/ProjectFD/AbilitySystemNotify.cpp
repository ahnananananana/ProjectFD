// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemNotify.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponentBase.h"

void UAbilitySystemNotify::Notify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference)
{
	Super::Notify(_pMeshComp, _pAnimation, _EventReference);

	if (IAbilitySystemInterface* pInterface = Cast<IAbilitySystemInterface>(_pMeshComp->GetOwner()))
	{
		if (UAbilitySystemComponentBase* pAbilitySystem = Cast<UAbilitySystemComponentBase>(pInterface->GetAbilitySystemComponent()))
		{
			pAbilitySystem->NotifyToAbilities(m_strEventName, _pMeshComp, _pAnimation, _EventReference);
		}
	}
}
