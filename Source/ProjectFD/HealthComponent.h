// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "HealthComponent.generated.h"

class UAttributeSetBase;
class UAbilitySystemComponent;

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFD_API UHealthComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FVoidTwoFloat OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FVoidTwoFloat OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FVoidTwoFloat OnHealthRegenChanged;

public:	
	UHealthComponent();

protected:
	UAttributeSetBase* CreateAttribute() override;
	void BindAttributeDelegates(UAbilitySystemComponent* _pAbilitySystempComp) override;

private:
	void HandleHealthChanged(const FOnAttributeChangeData& _ChangeData);
	void HandleHealthRegenChanged(const FOnAttributeChangeData& _ChangeData);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& _ChangeData);
};
