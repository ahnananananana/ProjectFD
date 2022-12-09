// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../ParagonCharacterBase.h"
#include "MinionCharacterBase.generated.h"

class UAbilitySystemComponent;
class UParagonCharacterAttributeSet;


UCLASS()
class PROJECTFD_API AMinionCharacterBase : public AParagonCharacterBase
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

public:
	AMinionCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void InitializeAbilitySystemComponent() override;
};
