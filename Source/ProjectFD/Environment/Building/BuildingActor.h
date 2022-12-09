// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interface/DeadInterface.h"
#include "../../Interface/HitableInterface.h"
#include "../../Interface/TeamInterface.h"
#include "../../CustomEnums.h"
#include "AbilitySystemInterface.h"
#include "BuildingActor.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class PROJECTFD_API ABuildingActor : public AActor, public IAbilitySystemInterface, public IDeadInterface, public IHitableInterface, public ITeamInterface
{
	GENERATED_BODY()

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY(EditAnywhere, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DefaultAttributeSetEffect;

	UPROPERTY(EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	ETeam Team;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

public:	
	// Sets default values for this actor's properties
	ABuildingActor();

	virtual ETeam GetTeam_Implementation() const override { return Team; }
	virtual void SetTeam_Implementation(ETeam NewTeam) override { Team = NewTeam; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
	virtual bool CanHit_Implementation() const override;
	virtual bool IsDead_Implementation() const override;
	virtual void SetDead() override;
	virtual FOnDead& OnDeadEvent_implementation(){return OnDead;}

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
};
