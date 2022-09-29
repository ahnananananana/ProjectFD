// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FVoidTwoFloat, float, NewValue, float, OldValue);

UCLASS()
class PROJECTFD_API UCustomDelegates : public UObject
{
	GENERATED_BODY()
};
