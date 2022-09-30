
#include "HealthComponent.h"
#include "HealthAttribute.h"
#include "AbilitySystemComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UAttributeSetBase* UHealthComponent::CreateAttribute()
{
	return NewObject<UHealthAttribute>(GetOwner());
}

void UHealthComponent::BindAttributeDelegates(UAbilitySystemComponent* _pAbilitySystempComp)
{
	_pAbilitySystempComp->GetGameplayAttributeValueChangeDelegate(UHealthAttribute::GetHealthAttribute()).AddUObject(this, &ThisClass::HandleHealthChanged);
	_pAbilitySystempComp->GetGameplayAttributeValueChangeDelegate(UHealthAttribute::GetHealthRegenAttribute()).AddUObject(this, &ThisClass::HandleHealthRegenChanged);
	_pAbilitySystempComp->GetGameplayAttributeValueChangeDelegate(UHealthAttribute::GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
}

void UHealthComponent::HandleHealthChanged(const FOnAttributeChangeData& _ChangeData)
{
	UE_LOG(LogTemp, Log, TEXT("%f %f"), _ChangeData.NewValue, _ChangeData.OldValue);
	OnHealthChanged.Broadcast(_ChangeData.NewValue, _ChangeData.OldValue);
}

void UHealthComponent::HandleHealthRegenChanged(const FOnAttributeChangeData& _ChangeData)
{
	OnHealthRegenChanged.Broadcast(_ChangeData.NewValue, _ChangeData.OldValue);
}

void UHealthComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& _ChangeData)
{
	OnMaxHealthChanged.Broadcast(_ChangeData.NewValue, _ChangeData.OldValue);
}