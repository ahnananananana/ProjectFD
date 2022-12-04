

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "TestPlayerState.generated.h"

class UTestAbilitySystemComponent;
class UAbilitySystemComponent;

UCLASS()
class PROJECTFD_API ATestPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UTestAbilitySystemComponent* m_pASC;

public:
	ATestPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	void BeginPlay() override;
};
