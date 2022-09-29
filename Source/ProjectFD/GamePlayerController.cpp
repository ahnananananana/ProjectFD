// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "GameBaseCharacter.h"


void AGamePlayerController::OnPossess(APawn* _pPawn)
{
	Super::OnPossess(_pPawn);
	m_pPossessedCharacter = Cast<AGameBaseCharacter>(_pPawn);
}

void AGamePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	m_pPossessedCharacter = nullptr;
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AGamePlayerController::OnJumpInput);
	InputComponent->BindAxis(TEXT("Move Forward"), this, &AGamePlayerController::OnMoveForwardInput);
	InputComponent->BindAxis(TEXT("Move Right"), this, &AGamePlayerController::OnMoveRightInput);
	InputComponent->BindAxis(TEXT("Look Up"), this, &AGamePlayerController::OnLookUpInput);
	InputComponent->BindAxis(TEXT("Look Right"), this, &AGamePlayerController::OnLookRightInput);
}

void AGamePlayerController::OnJumpInput()
{
	if(!m_pPossessedCharacter)
		return;

	m_pPossessedCharacter->Jump();
}

void AGamePlayerController::OnMoveForwardInput(float _fValue)
{
	if (!m_pPossessedCharacter)
		return;

	FVector vForward = PlayerCameraManager->GetActorForwardVector();
	vForward.Z = 0;
	vForward.Normalize();

	m_pPossessedCharacter->AddMovementInput(vForward, _fValue);
}

void AGamePlayerController::OnMoveRightInput(float _fValue)
{
	if (!m_pPossessedCharacter)
		return;

	FVector vRight = PlayerCameraManager->GetActorRightVector();
	vRight.Z = 0;
	vRight.Normalize();

	m_pPossessedCharacter->AddMovementInput(vRight, _fValue);
}

void AGamePlayerController::OnLookUpInput(float _fValue)
{
	if (!m_pPossessedCharacter)
		return;

	AddPitchInput(_fValue);
}

void AGamePlayerController::OnLookRightInput(float _fValue)
{
	if (!m_pPossessedCharacter)
		return;

	AddYawInput(_fValue);
}