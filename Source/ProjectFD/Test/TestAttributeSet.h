#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TestAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTFD_API UTestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;

public:
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Health)

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	void OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute, FAggregator* NewAggregator) const override;

private:
	UFUNCTION(meta = (AllowPrivateAccess = "true"))
	void OnRep_Health(const FGameplayAttributeData& OldValue);
};
