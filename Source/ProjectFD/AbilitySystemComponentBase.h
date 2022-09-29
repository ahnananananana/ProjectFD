
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "AbilitySystemComponentBase.generated.h"

UCLASS()
class PROJECTFD_API UAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UAbilitySystemComponentBase();

	void InitAttribute(const FDataTableRowHandle& _DataHandle);
};
