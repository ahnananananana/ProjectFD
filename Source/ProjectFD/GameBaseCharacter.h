// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CustomEnums.h"
#include "CustomStruct.h"
#include "HealthInterface.h"
#include "GameBaseCharacter.generated.h"

class UGameplayAbility;
class UAbilitySystemComponentBase;
class UGameCharacterAttributeSet;

UCLASS(BlueprintType)
class PROJECTFD_API AGameBaseCharacter 
	: public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	FRotator m_rLookRotation;
	UHealthComponent* m_pHealthComp;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Default Ability", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> m_arrInitialAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Base Data", meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle m_BaseData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayAbility", DisplayName = "Default Abilitys", meta = (AllowPrivateAccess = "true"))
	TMap<EInput, TSubclassOf<UGameplayAbility>> m_mapAbility;

	FCharacterData* m_pCharacterData;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
//Gameplay Ability System End

	FCharacterData* GetCharacterData() const { return m_pCharacterData; }

public:
	FRotator GetLookRotation() const { return m_rLookRotation; }
	//double GetLeftTurnAngle() const { return m_qTargetRot.Rotator().Yaw - GetActorRotation().Yaw; }

public:
	AGameBaseCharacter();

protected:
	void BeginPlay() override;

public:
	void Tick(float _fDeltaTime) override;

private:
	//void Turn(double _dAngle);
};
