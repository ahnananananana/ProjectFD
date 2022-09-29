// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetBase.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UAttributeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	m_pAttribute = CreateAttribute();

	m_pAbilitySystemComp = Cast<UAbilitySystemComponent>(GetOwner()->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
	m_pAbilitySystemComp->AddAttributeSetSubobject(m_pAttribute);

	BindAttributeDelegates(m_pAbilitySystemComp);
}