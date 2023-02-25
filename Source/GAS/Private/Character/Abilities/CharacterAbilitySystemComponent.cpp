// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/CharacterAbilitySystemComponent.h"

void UCharacterAbilitySystemComponent::ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float UnmitigateDamage, float MitigatedDamage)
{

	ReceivedDamage.Broadcast(SourceASC, UnmitigateDamage, MitigatedDamage);
}
