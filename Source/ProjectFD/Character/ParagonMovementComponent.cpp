// Copyright ahnananananana. All Rights Reserved.


#include "ParagonMovementComponent.h"
#include "ParagonCharacterBase.h"
#include "../CustomMacros.h"
#include "AbilitySystemComponent.h"
#include "ParagonCharacterAttributeSet.h"

float UParagonMovementComponent::GetMaxSpeed() const
{
	if (MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking)
	{
		AParagonCharacterBase* Owner = Cast<AParagonCharacterBase>(GetCharacterOwner());
		ENSURE(Owner, 0);

		const UParagonCharacterAttributeSet* AttributeSet = Owner->GetAbilitySystemComponent()->GetSet<UParagonCharacterAttributeSet>();
		ENSURE(AttributeSet, 0);

		return AttributeSet->GetMoveSpeed();
	}
	else
	{
		return Super::GetMaxSpeed();
	}
}