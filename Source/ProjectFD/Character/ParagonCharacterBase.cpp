// Copyright ahnananananana. All Rights Reserved.

#include "ParagonCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterAbilitySetBase.h"
#include "../Player/ParagonPlayerState.h"
#include "../AI/ParagonAIControllerBase.h"
#include "../CustomMacros.h"
#include "Abilities/GameplayAbilityBase.h"
#include "ParagonMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "ParagonCharacterAttributeSet.h"

AParagonCharacterBase::AParagonCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UParagonMovementComponent>(ACharacter::CharacterMovementComponentName))
	, Team(ETeam::None)
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName(TEXT("State.Dead")));
}

bool AParagonCharacterBase::IsDead_Implementation() const
{
	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	ENSURE(asc, false);
	return asc->HasMatchingGameplayTag(DeadTag);
}

bool AParagonCharacterBase::CanHit_Implementation() const
{
	return !IsDead_Implementation();
}

void AParagonCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AParagonCharacterBase, CurLocoState);
}

//void AParagonCharacterBase::SetLocomotionState_Implementation(ELocomotionState NewState)
//{
//	if (CurLocoState == NewState)
//	{
//		return;
//	}
//
//	CurLocoState = NewState;
//}

void AParagonCharacterBase::SetDead()
{
	if (IsDead_Implementation())
	{
		return;
	}

	UAbilitySystemComponent* asc = GetAbilitySystemComponent();
	ENSURE(asc);

	asc->CancelAllAbilities();

	asc->AddLooseGameplayTag(DeadTag);
	PlayAnimMontage(DeadMontage);

	SetActorEnableCollision(false);

	OnDead.Broadcast(this);
}

//void AParagonCharacterBase::LookToward(const FVector& TargetLook)
//{
//	TargetLookDir = TargetLook;
//	TargetLookDir.Z = 0;
//	TargetLookDir.Normalize();
//}

//void AParagonCharacterBase::LookAt(const FVector& TargetLookAt)
//{
//	LookToward(TargetLookAt - GetActorLocation());
//}

//ASC 초기화 서버용
void AParagonCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeAbilitySystemComponent();
}

void AParagonCharacterBase::InitializeAttributes(UAbilitySystemComponent* AbilitySystemComp)
{
	ENSURE(AbilitySystemComp);
	ENSURE(DefaultAttributeEffect);

	// 스탯 초기화
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
		ENSURE(NewHandle.IsValid());
		AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}

	// 스탯 콜백 등록
	{
		const UParagonCharacterAttributeSet* Attribute = Cast<UParagonCharacterAttributeSet>(AbilitySystemComp->GetAttributeSet(UParagonCharacterAttributeSet::StaticClass()));
		ENSURE(Attribute);
		Attribute->OnAttributeChange.AddDynamic(this, &AParagonCharacterBase::OnAttributeChanged);
	}
}

void AParagonCharacterBase::InitializeAbilities(UAbilitySystemComponent* AbilitySystemComp)
{
	ENSURE(AbilitySystemComp);

	if (HasAuthority())
	{
		AbilitySystemComp->ClearAllAbilities();

		for (TSubclassOf<UGameplayAbilityBase>& Ability : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->GetInputID()), this));
		}
	}
}

void AParagonCharacterBase::OnAttributeChanged(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (Attribute == UParagonCharacterAttributeSet::GetHealthAttribute())
	{
		if (NewValue <= 0.f && !IsDead_Implementation())
		{
			SetDead();
		}
	}
}