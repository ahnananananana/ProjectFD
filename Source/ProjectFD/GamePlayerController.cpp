// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "Character/ParagonCharacterBase.h"

void AGamePlayerController::OnPossess(APawn* PawnToPossess)
{
	Super::OnPossess(PawnToPossess);
	PossessedCharacter = Cast<AParagonCharacterBase>(PawnToPossess);;
}

void AGamePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedCharacter = nullptr;
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	PossessedCharacter = Cast<AParagonCharacterBase>(GetPawn());
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AGamePlayerController::OnJumpInput);
	InputComponent->BindAxis(TEXT("Move Forward"), this, &AGamePlayerController::OnMoveForwardInput);
	InputComponent->BindAxis(TEXT("Move Right"), this, &AGamePlayerController::OnMoveRightInput);
	InputComponent->BindAxis(TEXT("Look Up"), this, &AGamePlayerController::OnLookUpInput);
	InputComponent->BindAxis(TEXT("Look Right"), this, &AGamePlayerController::OnLookRightInput);

	/*InputComponent->BindAction<FActivateAbiltyDelegate>(TEXT("Primary Action"), IE_Pressed, this, &AGamePlayerController::OnActivateAbility, EInput::PRIMARY_ACTION);
	InputComponent->BindAction<FActivateAbiltyDelegate>(TEXT("Secondary Action"), IE_Pressed, this, &AGamePlayerController::OnActivateAbility, EInput::SECONDARY_ACTION);
	InputComponent->BindAction<FActivateAbiltyDelegate>(TEXT("Skill1"), IE_Pressed, this, &AGamePlayerController::OnActivateAbility, EInput::SKILL1);
	InputComponent->BindAction<FActivateAbiltyDelegate>(TEXT("Skill2"), IE_Pressed, this, &AGamePlayerController::OnActivateAbility, EInput::SKILL2);
	InputComponent->BindAction<FActivateAbiltyDelegate>(TEXT("Ultimate"), IE_Pressed, this, &AGamePlayerController::OnActivateAbility, EInput::ULTIMATE);*/
}

void AGamePlayerController::OnActivateAbility(const EInput _eType)
{
	//PossessedCharacter->ActivateAbility(_eType);
}

void AGamePlayerController::OnJumpInput()
{
	if (!PossessedCharacter)
	{
		return;
	}

	PossessedCharacter->Jump();
}

void AGamePlayerController::OnMoveForwardInput(float Value)
{
	if (!PossessedCharacter)
	{
		return;
	}

	FVector vForward = PlayerCameraManager->GetActorForwardVector();
	vForward.Z = 0;
	vForward.Normalize();

	PossessedCharacter->AddMovementInput(vForward, Value);
}

void AGamePlayerController::OnMoveRightInput(float Value)
{
	if (!PossessedCharacter)
	{
		return;
	}

	FVector vRight = PlayerCameraManager->GetActorRightVector();
	vRight.Z = 0;
	vRight.Normalize();

	PossessedCharacter->AddMovementInput(vRight, Value);
}

void AGamePlayerController::OnLookUpInput(float Value)
{
	if (!PossessedCharacter)
	{
		return;
	}

	AddPitchInput(Value);
}

void AGamePlayerController::OnLookRightInput(float Value)
{
	if (!PossessedCharacter)
	{
		return;
	}

	AddYawInput(Value);
}