// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstanceBase.h"
#include "GameBaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

void UCharacterAnimInstanceBase::NativeBeginPlay()
{
	m_pOwner = Cast<AGameBaseCharacter>(GetOwningActor());
	if (m_pOwner)
	{
		m_pOwnerMovement = m_pOwner->GetMovementComponent();
	}
}

void UCharacterAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!m_pOwner)
		return;

	if (!m_pOwnerMovement)
		return;

	m_bIsInAir = m_pOwnerMovement->IsFalling() || m_pOwnerMovement->IsFlying() || m_pOwner->IsJumpProvidingForce();

	m_bIsMoveInputExist = m_pOwner->GetLastMovementInputVector() != FVector::ZeroVector;

	m_vMoveDirection = m_pOwner->GetVelocity();

	m_dSpeed = m_vMoveDirection.Size();
	m_dSpeedRatio = m_vMoveDirection.Size() / m_pOwnerMovement->GetMaxSpeed();

	m_vMoveDirection.Z = 0;
	m_vMoveDirection.Normalize();

	m_rLookRotation = m_pOwner->GetLookRotation();

	double dMoveYaw = m_vMoveDirection.Rotation().Yaw;
	double dViewYaw = m_pOwner->GetViewRotation().Yaw;

	if (dMoveYaw < dViewYaw)
	{
		m_dMoveAngle = 360 - (dViewYaw - dMoveYaw);
	}
	else
	{
		m_dMoveAngle = dMoveYaw - dViewYaw;
	}

	if (m_dMoveAngle > 180)
		m_dMoveAngle -= 360;

	//m_dLeftTurnAngle = m_pOwner->GetLeftTurnAngle();
}
