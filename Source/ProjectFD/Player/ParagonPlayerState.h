// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ParagonPlayerState.generated.h"

class UAbilitySystemComponent;

UCLASS()
class PROJECTFD_API AParagonPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

public:
	AParagonPlayerState();

	virtual void BeginPlay() override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }
};


