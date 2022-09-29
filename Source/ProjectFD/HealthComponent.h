// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "HealthComponent.generated.h"

class UAttributeSetBase;
class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFD_API UHealthComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:
	FVoidTwoFloat OnHealthChanged;
	FVoidTwoFloat OnMaxHealthChanged;
	FVoidTwoFloat OnHealthRegenChanged;

public:	
	UHealthComponent();

protected:
	UAttributeSetBase* CreateAttribute() override;
	void BindAttributeDelegates(UAbilitySystemComponent* _pAbilitySystempComp) override;

private:
	void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	void HandleHealthRegenChanged(const FOnAttributeChangeData& ChangeData);
	void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
};
