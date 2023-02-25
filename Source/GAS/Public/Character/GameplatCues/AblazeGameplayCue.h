// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "AblazeGameplayCue.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AAblazeGameplayCue : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
public:
	AAblazeGameplayCue();

	FGameplayTag Ablaze;
};
