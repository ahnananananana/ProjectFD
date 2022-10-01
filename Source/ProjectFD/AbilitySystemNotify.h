// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AbilitySystemNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTFD_API UAbilitySystemNotify : public UAnimNotify
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, DisplayName = "Event Name", meta = (AllowPrivateAccess))
	FString m_strEventName;

	void Notify(USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& EventReference) override;
};
