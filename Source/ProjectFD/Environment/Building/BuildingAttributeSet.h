// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../../CustomMacros.h"
#include "../../AttributeSetBase.h"
#include "BuildingAttributeSet.generated.h"

UCLASS()
class PROJECTFD_API UBuildingAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_AttackDamage, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackDamage;

public:
	ATTRIBUTE_ACCESSORS(UBuildingAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBuildingAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBuildingAttributeSet, AttackDamage);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UBuildingAttributeSet, Health, OldValue); }
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UBuildingAttributeSet, MaxHealth, OldValue); }
	UFUNCTION()
	void OnRep_AttackDamage(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UBuildingAttributeSet, AttackDamage, OldValue); }

};
