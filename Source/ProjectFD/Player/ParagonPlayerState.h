// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "ParagonPlayerState.generated.h"

class UAbilitySystemComponent;
class UParagonCharacterAttributeSet;
struct FGameplayAttribute;

UCLASS()
class PROJECTFD_API AParagonPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;
	TObjectPtr<UParagonCharacterAttributeSet> AttributeSet;

public:
	AParagonPlayerState();

	virtual void BeginPlay() override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComp; }

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
};


