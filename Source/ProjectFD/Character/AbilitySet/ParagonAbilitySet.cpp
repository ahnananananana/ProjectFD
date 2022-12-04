// Copyright ahnananananana. All Rights Reserved.


#include "ParagonAbilitySet.h"
#include "AbilitySystemComponent.h"

void UParagonAbilitySet::GrantAbilities(UAbilitySystemComponent* AbilitySystemComp) const
{
	AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(Death));
	/*for (FAbilityBindInfo& info : DefaultAbilities)
	{
		AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(info.AbilityClass, 1, static_cast<int32>(info.InputID), this));
	}*/
}
