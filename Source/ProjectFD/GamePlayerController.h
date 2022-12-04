// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomEnums.h"
#include "GamePlayerController.generated.h"

class AParagonCharacterBase;

UCLASS()
class PROJECTFD_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	TObjectPtr<AParagonCharacterBase> PossessedCharacter;

	float m_fLookUpSpeed = 1.f;
	float m_fLookRightSpeed = 1.f;

protected:
	void OnPossess(APawn* PawnToPossess) override;
	void OnUnPossess() override;
	void SetupInputComponent() override;

	void BeginPlay() override;

private:
	void OnJumpInput();
	void OnMoveForwardInput(float Value);
	void OnMoveRightInput(float Value);
	void OnLookUpInput(float Value);
	void OnLookRightInput(float Value);
	void OnActivateAbility(const EInput _eType);

	DECLARE_DELEGATE_OneParam(FActivateAbiltyDelegate, const EInput);
};
