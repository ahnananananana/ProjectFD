// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "../CustomMacros.h"
#include "ParagonCharacterAttributeSet.generated.h"

UCLASS()
class PROJECTFD_API UParagonCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxMana, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxMana;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_BasicAttackDamage, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData BasicAttackDamage;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MoveSpeed, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MoveSpeed;

public:
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, BasicAttackDamage);
	ATTRIBUTE_ACCESSORS(UParagonCharacterAttributeSet, MoveSpeed);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, Health, OldValue); }
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, MaxHealth, OldValue); }
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, Mana, OldValue); }
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, MaxMana, OldValue); }
	UFUNCTION()
	void OnRep_BasicAttackDamage(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, BasicAttackDamage, OldValue); }
	UFUNCTION()
	void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue) { GAMEPLAYATTRIBUTE_REPNOTIFY(UParagonCharacterAttributeSet, MoveSpeed, OldValue); }

public:
	void Init(FDataTableRowHandle& Handle);

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
