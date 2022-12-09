// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DeadInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, AActor*, DeadActor);

UINTERFACE(Blueprintable, MinimalAPI)
class UDeadInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTFD_API IDeadInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead() const;
	virtual bool IsDead_Implementation() const = 0;

	virtual void SetDead() = 0;
};
