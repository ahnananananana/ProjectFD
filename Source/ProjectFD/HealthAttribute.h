// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "HealthAttribute.generated.h"

UCLASS()
class PROJECTFD_API UHealthAttribute : public UAttributeSetBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_HealthRegen, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData HealthRegen;

public:
	ATTRIBUTE_ACCESSORS(UHealthAttribute, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttribute, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthAttribute, HealthRegen);

public:
	UHealthAttribute();

protected:
	void OnInit(const FCharacterData& _Data) override;

public:
	void PreAttributeChange(const FGameplayAttribute& _Attribute, float& _fNewValue) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& _OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& _oldValue);
	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& _oldValue);
};
