// Copyright ahnananananana. All Rights Reserved.


#include "BuildingActor.h"
#include "AbilitySystemComponent.h"
#include "../../Character/ParagonCharacterAttributeSet.h"

// Sets default values
ABuildingActor::ABuildingActor()
	: Team(ETeam::None)
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Comp"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//CreateDefaultSubobject<UParagonCharacterAttributeSet>(TEXT("AttributeSet"));
}

bool ABuildingActor::CanHit_Implementation() const
{
	return !IsDead_Implementation();
}

bool ABuildingActor::IsDead_Implementation() const
{
	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	ENSURE(asc, false);
	return asc->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("State.Dead")));
}

void ABuildingActor::SetDead()
{
	if (IsDead_Implementation())
	{
		return;
	}

	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	ENSURE(asc);
	asc->CancelAllAbilities();
	asc->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("State.Dead")));

	OnDead.Broadcast(this);
}

void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();

	ENSURE(AbilitySystemComp);
	ENSURE(DefaultAttributeSetEffect);

	AbilitySystemComp->InitAbilityActorInfo(this, this);

	UParagonCharacterAttributeSet* AttributeSet = NewObject<UParagonCharacterAttributeSet>(this);
	AbilitySystemComp->AddAttributeSetSubobject(AttributeSet);

	AttributeSet->OnAttributeChange.AddDynamic(this, &ABuildingActor::OnAttributeChanged);

	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeSetEffect, 1, EffectContext);
		ENSURE(NewHandle.IsValid());
		AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}

void ABuildingActor::OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	UE_LOG(LogTemp, Log, TEXT("OnAttributeChanged %f %f"), OldValue, NewValue);
	if (Attribute == UParagonCharacterAttributeSet::GetHealthAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("if (Attribute == UParagonCharacterAttributeSet::GetHealthAttribute()) %f %f"), OldValue, NewValue);
		if (NewValue <= 0.f && !IsDead_Implementation())
		{
			UE_LOG(LogTemp, Log, TEXT("if (NewValue <= 0.f && !IsDead_Implementation())"));
			SetDead();
		}
	}
}