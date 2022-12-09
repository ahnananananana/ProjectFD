// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "HeroAIControllerBase.generated.h"


UCLASS()
class PROJECTFD_API AHeroAIControllerBase : public AAIController, public IAbilitySystemInterface
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
};
