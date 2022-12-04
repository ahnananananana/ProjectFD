// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAbilitySetBase.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;

UCLASS(Abstract)
class PROJECTFD_API UCharacterAbilitySetBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GrantAbilities(UAbilitySystemComponent* AbilitySystemComp) const PURE_VIRTUAL(GrantAbilities);
};
