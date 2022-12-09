// Copyright ahnananananana. All Rights Reserved.


#include "MinionCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "../ParagonCharacterAttributeSet.h"

AMinionCharacterBase::AMinionCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//TODO: 왠지 모르게 가비지 컬렉터에 걸림
	//AttributeSet = CreateDefaultSubobject<UParagonCharacterAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMinionCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AMinionCharacterBase::InitializeAbilitySystemComponent()
{
	AbilitySystemComp->AddDefaultSubobjectSet(NewObject<UParagonCharacterAttributeSet>(this));

	AbilitySystemComp->InitAbilityActorInfo(this, this);
	InitializeAttributes(AbilitySystemComp);
	InitializeAbilities(AbilitySystemComp);
}