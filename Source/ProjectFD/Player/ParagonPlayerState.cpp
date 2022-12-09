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

	AttributeSet = CreateDefaultSubobject<UParagonCharacterAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void AParagonPlayerState::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComp->SetOwnerActor(this);

	AttributeSet->OnAttributeChange.AddDynamic(this, &AParagonPlayerState::OnAttributeChanged);
}

void AParagonPlayerState::OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == AttributeSet->GetHealthAttribute())
	{
		if (NewValue <= 0.f)
		{

		}
	}
	else if (Attribute == AttributeSet->GetMaxHealthAttribute())
	{

	}
}