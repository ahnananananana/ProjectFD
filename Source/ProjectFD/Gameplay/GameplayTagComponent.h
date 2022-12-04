// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagComponent.generated.h"

class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFD_API UGameplayTagComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, DisplayName = "Owned Tags")
	FGameplayTagContainer OwnedTags;

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

public:	
	UGameplayTagComponent();

	virtual void BeginPlay() override;

	bool HasTag(const FGameplayTag& TagToCheck, bool bMustMatchFull = false) const;
	void AddTags(const FGameplayTagContainer& TagsToAdd);
	void RemoveTags(const FGameplayTagContainer& TagsToRemove);
};
