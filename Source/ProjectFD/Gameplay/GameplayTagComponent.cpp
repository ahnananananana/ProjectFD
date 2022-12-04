// Copyright ahnananananana. All Rights Reserved.

#include "GameplayTagComponent.h"
#include "AbilitySystemComponent.h"

UGameplayTagComponent::UGameplayTagComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameplayTagComponent::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComp = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
}

bool UGameplayTagComponent::HasTag(const FGameplayTag& TagToCheck, bool bMustMatchFull) const
{
	bool bResult = bMustMatchFull ? OwnedTags.HasTagExact(TagToCheck) : OwnedTags.HasTag(TagToCheck);

	if (AbilitySystemComp)
	{
		FGameplayTagContainer ASCTags;
		AbilitySystemComp->GetOwnedGameplayTags(ASCTags);
		bResult |= bMustMatchFull ? ASCTags.HasTagExact(TagToCheck) : ASCTags.HasTag(TagToCheck);
	}

	return bResult;
}

void UGameplayTagComponent::AddTags(const FGameplayTagContainer& TagsToAdd)
{
	for (const FGameplayTag& tag : TagsToAdd)
	{
		OwnedTags.AddTag(tag);
	}
}

void UGameplayTagComponent::RemoveTags(const FGameplayTagContainer& TagsToRemove)
{
	OwnedTags.RemoveTags(TagsToRemove);
}
