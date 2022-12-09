// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../CustomEnums.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "../Interface/DeadInterface.h"
#include "../Interface/HitableInterface.h"
#include "../Interface/TeamInterface.h"
#include "ParagonCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayAbilityBase;
class UGameplayEffect;
struct FGameplayAttribute;
class UAbilitySystemComponent;
class UCharacterAbilitySetBase;
class UAbilitySystemComponent;
class FObjectInitializer;
class UCameraComponent;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	None,
	Idle,
	Run,
};

UCLASS(Abstract)
class PROJECTFD_API AParagonCharacterBase : public ACharacter, public IAbilitySystemInterface, public IDeadInterface, public IHitableInterface, public ITeamInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbilityBase>> DefaultAbilities;

	/*UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	ELocomotionState CurLocoState;*/

	UPROPERTY(EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	ETeam Team;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DeadMontage;
	FGameplayTag DeadTag;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDead OnDead;

public:
	AParagonCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual ETeam GetTeam_Implementation() const override { return Team; }
	virtual void SetTeam_Implementation(ETeam NewTeam) override { Team = NewTeam; }

	virtual bool IsDead_Implementation() const override;
	virtual bool CanHit_Implementation() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return nullptr;}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void LookToward(const FVector& TargetLook);
	void LookAt(const FVector& TargetLookAt);

	virtual void SetDead() override;
	virtual FOnDead& OnDeadEvent_implementation() { return OnDead; }

protected:
	void PossessedBy(AController* NewController) override;

	//MoveYaw와 LocoState는 애니메이션을 위한 것이므로 조금 틀려도 괜찮을 듯
	/*UFUNCTION(Server, Unreliable)
	void SetLocomotionState(ELocomotionState NewState);*/

	virtual void InitializeAbilitySystemComponent() PURE_VIRTUAL(InitializeAbilitySystemComponent);
	void InitializeAttributes(UAbilitySystemComponent* AbilitySystemComp);
	void InitializeAbilities(UAbilitySystemComponent* AbilitySystemComp);

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
};
