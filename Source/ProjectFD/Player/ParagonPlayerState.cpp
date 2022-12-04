// Copyright ahnananananana. All Rights Reserved.

#include "ParagonPlayerState.h"
#include "AbilitySystemComponent.h"
#include "../CustomMacros.h"
#include "../Character/ParagonCharacterAttributeSet.h"


AParagonPlayerState::AParagonPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CreateDefaultSubobject<UParagonCharacterAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AParagonPlayerState::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComp->SetOwnerActor(this);
}
