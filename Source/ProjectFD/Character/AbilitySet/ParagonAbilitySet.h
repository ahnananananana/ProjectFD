// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../CharacterAbilitySetBase.h"
#include "ParagonAbilitySet.generated.h"

UCLASS()
class PROJECTFD_API UParagonAbilitySet : public UCharacterAbilitySetBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Death;

public:
	virtual void GrantAbilities(UAbilitySystemComponent* AbilitySystemComp) const override;
};
