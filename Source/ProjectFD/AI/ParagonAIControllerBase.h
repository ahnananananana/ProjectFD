// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AbilitySystemInterface.h"
#include "ParagonAIControllerBase.generated.h"

class UAbilitySystemComponent;

UCLASS()
class PROJECTFD_API AParagonAIControllerBase : public AAIController, public IAbilitySystemInterface
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
};
