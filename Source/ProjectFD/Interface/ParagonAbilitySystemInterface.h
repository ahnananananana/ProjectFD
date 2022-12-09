// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilitySystemInterface.h"
#include "ParagonAbilitySystemInterface.generated.h"

class UAbilitySystemComponent;
class FOnAttributeChange;

UINTERFACE(MinimalAPI)
class UParagonAbilitySystemInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTFD_API IParagonAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual FOnAttributeChange& GetOnAttributeChange() = 0;
};
