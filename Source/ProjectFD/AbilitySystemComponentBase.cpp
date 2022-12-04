// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemComponentBase.h"
#include "AttributeSetBase.h"
//#include "GameplayAbilityBase.h"
#include "GameplayAbilitySet.h"
UAbilitySystemComponentBase::UAbilitySystemComponentBase()
{
}

void UAbilitySystemComponentBase::NotifyToAbilities(
	const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, 
	UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference
	)
{
	/*for (const FGameplayAbilitySpec& spec : ActivatableAbilities.Items)
	{
		for (UGameplayAbility* pAbility : spec.GetAbilityInstances())
		{
			if (UGameplayAbilityBase* pAbilityBase = Cast<UGameplayAbilityBase>(pAbility))
			{
				pAbilityBase->OnNotify(_strEventName, _pMeshComp, _pAnimation, _EventReference);
			}
		}
	}*/
}