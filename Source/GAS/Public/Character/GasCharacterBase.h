// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GAS/GAS.h>
#include "GameplayTagContainer.h"
#include "GasCharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, AGasCharacterBase*, Character);

UCLASS()
class GAS_API AGasCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGasCharacterBase(const class FObjectInitializer& ObjectInitializer);

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintAssignable, Category = "GAS | Character")
		FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BlueprintCallable, Category = "GAS | Character")
		virtual bool  IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "GAS | Character")
		virtual int32 GetAbilityLevel(GasAbilityId AbilityId) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable,Category = "GAS | Character")
	virtual void FinishDying();

	float GetCharacterLevel();


	//Attributes

	UFUNCTION(BlueprintCallable, Category = "GAS | Character | Attributes")
		float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS | Character | Attributes")
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS | Character | Attributes")
		float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "GAS | Character | Attributes")
		float GetMaxMana() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UCharacterAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UCharacterAttributeSetBase> AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS | Animations")
		TArray<TSubclassOf<class UCharacterGameplayAbility>> CharacterAbilities;
	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS | Character")
		FName CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS | Animations")
		class UAnimMontage* DeadMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS | Animations")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;

	//Attribute lara gelicek görsel efektler
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS | Animations")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();

	//Running On The Server
	virtual void InitializeAttributes();


	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);

	virtual void SetMana(float Mana);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
