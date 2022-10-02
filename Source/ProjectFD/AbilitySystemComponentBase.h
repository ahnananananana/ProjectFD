
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataTable.h"
#include "AbilitySystemComponentBase.generated.h"

UCLASS(BlueprintType)
class PROJECTFD_API UAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAbilitySystemComponentBase();

	void InitAttribute(const FDataTableRowHandle& _DataHandle);
	void NotifyToAbilities(const FString& _strEventName, USkeletalMeshComponent* _pMeshComp, UAnimSequenceBase* _pAnimation, const FAnimNotifyEventReference& _EventReference);
};
