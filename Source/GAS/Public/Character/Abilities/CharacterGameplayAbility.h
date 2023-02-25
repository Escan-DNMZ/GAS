// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/GAS.h"
#include "CharacterGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UCharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		GasAbilityId AbilityInputID = GasAbilityId::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		GasAbilityId AbilityID = GasAbilityId::None;


	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
