// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HitableInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UHitableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTFD_API IHitableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanHit() const;
	virtual bool CanHit_Implementation() const = 0;
};
