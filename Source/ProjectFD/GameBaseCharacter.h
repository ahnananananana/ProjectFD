// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CustomEnums.h"
#include "CustomStruct.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayAbilityBase.h"
#include "GameBaseCharacter.generated.h"

class UGameplayAbility;
class UAbilitySystemComponentBase;
class UGameCharacterAttributeSet;
class UHealthComponent;
class UAnimMontage;
class UPlayerCharacterAbility;

USTRUCT(BlueprintType)
struct FAbilityInitInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Input")
	EInput Input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Ability")
	TSubclassOf<UGameplayAbilityBase> Ability;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Ability Info")
	FAbilityInfo AbilityInfo;*/
};

UCLASS(BlueprintType)
class PROJECTFD_API AGameBaseCharacter 
	: public ACharacter, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

	FRotator m_rLookRotation;
	UPROPERTY(EditAnyWhere, DisplayName = "Owned Tags")
	FGameplayTagContainer m_OwnedTags;

	UPROPERTY(EditAnyWhere, DisplayName = "UGameplayEffect")
	TSubclassOf<UGameplayEffect> m_testEffect;

	UPROPERTY(EditAnyWhere, DisplayName = "UGameplayEffect")
	UGameCharacterAttributeSet* m_pAttributeSet;

	/*UPROPERTY(EditAnyWhere, DisplayName = "Turn Speed")
	double m_dTurnSpeed;
	UPROPERTY(EditDefaultsOnly, DisplayName = "Turn Curve")
	UCurveFloat* m_pTurnCurve;
	FQuat4d m_qTargetRot;
	float m_fTurnStartTime;
	bool m_bIsTurning;*/

//Gameplay Ability System Start
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "ASC", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponentBase* m_pAbilitySystemComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Attributes", meta = (AllowPrivateAccess = "true"))
	UGameCharacterAttributeSet* m_pAttributes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Base Data", meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle m_BaseData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Default Ability", meta = (AllowPrivateAccess = "true"))
	TArray<FAbilityInitInfo> m_arrDefaultAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Input Ability", meta = (AllowPrivateAccess = "true"))
	TMap<EInput, FGameplayAbilitySpecHandle> m_mapInputAbility;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Binded Ability", meta = (AllowPrivateAccess = "true"))
	TArray<FGameplayAbilitySpecHandle> m_arrBindedAbilities;

	FCharacterData* m_pCharacterData;

public:
	UFUNCTION(BlueprintCallable)
	FVector GetAimPoint() const;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	void GetOwnedGameplayTags(FGameplayTagContainer& _TagContainer) const override { _TagContainer = m_OwnedTags; }
	void AddGameplayTag(const FGameplayTag& _tag) { m_OwnedTags.AddTag(_tag); }
	//void RemoveGameplayTag(const FGameplayTag& _tag) { m_OwnedTags.Remove }
//Gameplay Ability System End

	FCharacterData* GetCharacterData() const { return m_pCharacterData; }

public:
	FRotator GetLookRotation() const { return m_rLookRotation; }
	//double GetLeftTurnAngle() const { return m_qTargetRot.Rotator().Yaw - GetActorRotation().Yaw; }

public:
	AGameBaseCharacter();

	void BindInputAbility(const EInput& _eInput, const FGameplayAbilitySpecHandle& _Handle);
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& _OutLifetimeProps) const override;

protected:
	void BeginPlay() override;

public:
	void Tick(float _fDeltaTime) override;
	UFUNCTION(Client, Reliable)
	void ActivateAbility(const EInput& _eType);

private:
	//void Turn(double _dAngle);
};
