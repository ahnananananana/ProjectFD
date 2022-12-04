// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ParagonAnimInstanceBase.generated.h"


class UAnimSequenceBase;

UCLASS()
class PROJECTFD_API UParagonAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimSequenceBase> LandSequence;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations")
	TObjectPtr<UAnimSequenceBase> JumpStartSequence;
};
