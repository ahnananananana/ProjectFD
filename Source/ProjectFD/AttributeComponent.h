// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomDelegates.h"
#include "AttributeComponent.generated.h"

class UAbilitySystemComponent;
class UAttributeSetBase;

UCLASS(ABSTRACT, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTFD_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	UAttributeSetBase* m_pAttribute;
	UAbilitySystemComponent* m_pAbilitySystemComp;

public:	
	UAttributeComponent();
	void InitializeComponent() override;
	
protected:
	virtual UAttributeSetBase* CreateAttribute() PURE_VIRTUAL(UAttributeComponent::Init, return nullptr;);
	virtual void BindAttributeDelegates(UAbilitySystemComponent* _pAbilitySystempComp) PURE_VIRTUAL(UAttributeComponent::BindAttributeDelegates);
};
