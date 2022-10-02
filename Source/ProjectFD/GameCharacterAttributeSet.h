#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "CustomMacros.h"
#include "GameCharacterAttributeSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, const FGameplayAttribute&, _Attribute, float, NewValue);


UCLASS()
class PROJECTFD_API UGameCharacterAttributeSet : public UAttributeSet
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
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_AttackDamage, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AttackDamage;

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FOnAttributeChanged OnAttributeValueChanged;

public:
	ATTRIBUTE_ACCESSORS(UGameCharacterAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UGameCharacterAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UGameCharacterAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UGameCharacterAttributeSet, MaxMana)
	ATTRIBUTE_ACCESSORS(UGameCharacterAttributeSet, AttackDamage)

public:
	UGameCharacterAttributeSet();

	void Init(FDataTableRowHandle& _handle);

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



private:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_AttackDamage(const FGameplayAttributeData& _oldValue);
};
