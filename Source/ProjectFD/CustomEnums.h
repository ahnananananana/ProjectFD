// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EInput : uint8
{
	NONE,
	PRIMARY_ACTION UMETA(DisplayName = "Primary Action"),
	SECONDARY_ACTION UMETA(DisplayName = "Secondary Action"),
	SKILL1 UMETA(DisplayName = "Skill1"),
	SKILL2 UMETA(DisplayName = "Skill2"),
	ULTIMATE UMETA(DisplayName = "Ultimate"),
	count,
};

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm			UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel			UMETA(DisplayName = "Cancel"),
	// 3 LMB
	BasicAttack		UMETA(DisplayName = "Basic Attack"),
	// 4 RMB
	Skill1			UMETA(DisplayName = "Skill1"),
	// 5 Q
	Skill2			UMETA(DisplayName = "Skill2"),
	// 6 E
	Skill3			UMETA(DisplayName = "Skill3"),
	// 7 R
	Ultimate		UMETA(DisplayName = "Ultimate"),
	// 8 Sprint
	Sprint			UMETA(DisplayName = "Sprint"),
	// 9 Jump
	Jump			UMETA(DisplayName = "Jump"),
};