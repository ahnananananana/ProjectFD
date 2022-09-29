
#include "HealthComponent.h"
#include "HealthAttribute.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"

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

void UHealthComponent::HandleHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}

void UHealthComponent::HandleHealthRegenChanged(const FOnAttributeChangeData& ChangeData)
{
	OnHealthRegenChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}

void UHealthComponent::HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxHealthChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue, GetInstigatorFromAttrChangeData(ChangeData));
}