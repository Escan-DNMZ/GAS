// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GasCharacterBase.h"
#include "Player/GASPlayerState.h"
#include "GasPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API AGasPlayerCharacter : public AGasCharacterBase
{
	GENERATED_BODY()

	
public:
	
	AGasPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	class USpringArmComponent* GetCameraBoom();

	class UCameraComponent* GetFollowCamera();

	UFUNCTION(BlueprintCallable, Category = "GAS|Camera")
		float GetStartingCameraBoomArmLength();



	UFUNCTION(BlueprintCallable, Category = "GAS|Camera")
		FVector GetStartingLocation();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "GAS|Camera")
		float BaseTurnRate = 45.0f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Camera")
		float BaseLookUpRate = 45.0f;


	UPROPERTY(BlueprintReadOnly, Category = "GAS|Camera")
		float StartingCameraBoomLength;

	UPROPERTY(BlueprintReadOnly, Category = "GAS|Camera")
	FVector StartingCameraBoomLocation;

	UFUNCTION(BlueprintCallable, Category = "GAS|Camera")
		FVector GetStartingCameraBoomLocation();

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere, Category = "GAS|Camera")
		class USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "GAS|Camera")
		class UCameraComponent* FollowCamera;

	bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	void LookUp(float Value);

	void LookUpRate(float Value);

	void Turn(float Value);

	void TurnRate(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void BindASCInput();

	void InitializeStartingValues(AGASPlayerState* PS);
};
