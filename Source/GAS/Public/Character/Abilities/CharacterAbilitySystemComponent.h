// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UCharacterAbilitySystemComponent*, SourceASC, float, UnmitigateDamage, float, MitigatedDamage);

UCLASS()
class GAS_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	//Alınan hasar değişkeninde hafifletilmiş ve hafifletilmemiş diye iki adet değişken bulunuyor eğer karakter armorluysa hasar hafifletilicek
	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float UnmitigateDamage, float MitigatedDamage);
};
