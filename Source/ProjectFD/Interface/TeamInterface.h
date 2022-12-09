// Copyright ahnananananana. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../CustomEnums.h"
#include "TeamInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UTeamInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTFD_API ITeamInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ETeam GetTeam() const;
	virtual ETeam GetTeam_Implementation() const = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTeam(ETeam NewTeam);
	virtual void SetTeam_Implementation(ETeam NewTeam) = 0;
};
