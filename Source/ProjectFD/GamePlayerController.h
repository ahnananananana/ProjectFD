// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class AGameBaseCharacter;

UCLASS()
class PROJECTFD_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	AGameBaseCharacter* m_pPossessedCharacter;

	float m_fLookUpSpeed = 1.f;
	float m_fLookRightSpeed = 1.f;


protected:
	void OnPossess(APawn* _pPawn) override;
	void OnUnPossess() override;
	void SetupInputComponent() override;

	void BeginPlay() override;

private:
	void OnJumpInput();
	void OnMoveForwardInput(float _fValue);
	void OnMoveRightInput(float _fValue);
	void OnLookUpInput(float _fValue);
	void OnLookRightInput(float _fValue);
};
