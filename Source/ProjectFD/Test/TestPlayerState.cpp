#include "TestPlayerState.h"
#include "TestAttributeSet.h"
#include "TestAbilitySystemComponent.h"
#include "../CustomMacros.h"

ATestPlayerState::ATestPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	m_pASC = CreateDefaultSubobject<UTestAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	m_pASC->SetIsReplicated(true);
	m_pASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CreateDefaultSubobject<UTestAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.0f;
}


UAbilitySystemComponent* ATestPlayerState::GetAbilitySystemComponent() const
{ 
	return m_pASC; 
}

void ATestPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ENSURE(m_pASC);

	m_pASC->SetOwnerActor(this);
}