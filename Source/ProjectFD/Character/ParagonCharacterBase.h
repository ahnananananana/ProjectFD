// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../CustomEnums.h"
#include "AbilitySystemInterface.h"
#include "ParagonCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayAbilityBase;
class UGameplayEffect;
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

USTRUCT(BlueprintType)
struct FAbilityBindInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	EAbilityInputID	InputID;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility>	AbilityClass;
};

UCLASS(Abstract)
class PROJECTFD_API AParagonCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbilityBase>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	ELocomotionState CurLocoState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_pCamera;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	bool bIsSprint;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Replicated, Category = "GamePlay", meta = (AllowPrivateAccess = "true"))
	double MoveYaw;

	bool bWasInputBindToAbilitySystem;
	FVector TargetLookDir;
	double TurnSpeed;
	double PreviousYaw;

public:
	AParagonCharacterBase(const FObjectInitializer& ObjectInitializer);

	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//MoveYaw와 LocoState는 애니메이션을 위한 것이므로 조금 틀려도 괜찮을 듯
	UFUNCTION(Server, Unreliable)
	void SetMoveYaw(double NewYaw);
	UFUNCTION(Server, Unreliable)
	void SetLocomotionState(ELocomotionState NewState);

protected:
	virtual void BeginPlay() override;
	void PossessedBy(AController* NewController) override;
	void OnRep_PlayerState() override;
	

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetSprint(bool bValue) { bIsSprint = bValue; }
	void LookToward(const FVector& TargetLook);
	void LookAt(const FVector& TargetLookAt);

private:
	void InitializeAbilitySystemComponent();
	void InitializeAttributes(UAbilitySystemComponent* AbilitySystemComp);
	void InitializeAbilities(UAbilitySystemComponent* AbilitySystemComp);
	void BindAbilitySystemToInputComponent(UAbilitySystemComponent* AbilitySystemComp);
};
