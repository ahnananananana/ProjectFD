// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityBase.h"
#include "PlayerCharacterAbility.generated.h"

UCLASS(BlueprintType, Abstract)
class PROJECTFD_API UPlayerCharacterAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, DisplayName = "UI Icon", meta =(AllowPrivateAccess))
	UTexture2D* m_pUIIcon;

public:
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual float GetCooldownTime() const;
};
