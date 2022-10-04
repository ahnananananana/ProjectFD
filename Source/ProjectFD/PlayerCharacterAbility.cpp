// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAbility.h"

float UPlayerCharacterAbility::GetCooldownTime() const
{
	float _, fResult;
	GetCooldownTimeRemainingAndDuration(CurrentSpecHandle, CurrentActorInfo, _, fResult);
	return fResult;
}