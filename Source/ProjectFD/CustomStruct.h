// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CustomStruct.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ManaRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> DeadMontages;
};