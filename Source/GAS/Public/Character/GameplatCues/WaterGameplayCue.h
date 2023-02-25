// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "WaterGameplayCue.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AWaterGameplayCue : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
public:
	AWaterGameplayCue();
	FGameplayTag Wet;

	UPROPERTY()
	class UBoxComponent* box;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> WetEffect;

	
};
