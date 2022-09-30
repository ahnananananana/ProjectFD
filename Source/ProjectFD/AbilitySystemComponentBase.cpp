// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemComponentBase.h"
#include "AttributeSetBase.h"
#include "GameplayAbilityBase.h"

UAbilitySystemComponentBase::UAbilitySystemComponentBase()
{
}

void UAbilitySystemComponentBase::InitAttribute(const FDataTableRowHandle& _DataHandle)
{
	for (UAttributeSet* pAttr : GetSpawnedAttributes_Mutable())
	{
		if (UAttributeSetBase* pAttrBase = Cast<UAttributeSetBase>(pAttr))
		{
			pAttrBase->Init(_DataHandle);
		}
		else
		{
			UE_LOG(LogScript, Warning, TEXT("Wrong AttributeSet!"));
		}
	}
}

void UAbilitySystemComponentBase::NotifyToAbilities(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference)
{
	for (const FGameplayAbilitySpec& spec : ActivatableAbilities.Items)
	{
		if (UGameplayAbilityBase* pAbility = Cast<UGameplayAbilityBase>(spec.Ability))
		{
			pAbility->OnNotify(_pMeshComp, _pAnimation, _EventReference);
		}
	}
}
