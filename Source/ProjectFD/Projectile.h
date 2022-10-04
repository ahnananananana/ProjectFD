// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameplayEffect.h>
#include "Projectile.generated.h"

UCLASS()
class PROJECTFD_API AProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayEffectSpecHandle m_effectHandle;

public:	
	// Sets default values for this actor's properties
	AProjectile();

	void SetEffectHandle(const FGameplayEffectSpecHandle& Handle) { m_effectHandle = Handle;}
};
