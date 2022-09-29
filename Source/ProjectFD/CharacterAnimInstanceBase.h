// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstanceBase.generated.h"

class AGameBaseCharacter;
class UPawnMovementComponent;

UCLASS()
class PROJECTFD_API UCharacterAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, DisplayName = "Speed")
	double m_dSpeed;
	/*UPROPERTY(BlueprintReadOnly, DisplayName = "Left Turn Angle")
	double m_dLeftTurnAngle;*/
	UPROPERTY(BlueprintReadOnly, DisplayName = "Move Direction")
	FVector m_vMoveDirection;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Is In Air")
	bool m_bIsInAir;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Is Move Input Exist")
	bool m_bIsMoveInputExist;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Look Rotation")
	FRotator m_rLookRotation;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Move Rotation")
	double m_dMoveAngle;
	UPROPERTY(BlueprintReadOnly, DisplayName = "Speed Ratio")
	double m_dSpeedRatio;


	AGameBaseCharacter* m_pOwner;
	UPawnMovementComponent* m_pOwnerMovement;
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
};
