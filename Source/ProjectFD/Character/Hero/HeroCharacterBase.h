// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../ParagonCharacterBase.h"
#include "HeroCharacterBase.generated.h"

UCLASS()
class PROJECTFD_API AHeroCharacterBase : public AParagonCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	//보는 방향과 움직이는 방향 사이의 각도
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	double MoveYaw;

	bool bWasInputBindToAbilitySystem;

public:
	AHeroCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetDead() override;

protected:
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void InitializeAbilitySystemComponent() override;

	UFUNCTION(Server, Unreliable)
	void SetMoveYaw(double NewYaw);

private:
	void BindAbilitySystemToInputComponent(UAbilitySystemComponent* AbilitySystemComp);
};
