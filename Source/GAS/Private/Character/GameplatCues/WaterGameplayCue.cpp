// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GameplatCues/WaterGameplayCue.h"
#include "GameplayCueNotify_Actor.h"
#include "Components/BoxComponent.h"
#include "Character/GasCharacterBase.h"
#include "GameplayAbilitySpec.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"

AWaterGameplayCue::AWaterGameplayCue()
{
	Wet = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Buff.Wet"));

	box = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	box->OnComponentBeginOverlap.AddDynamic(this, &AWaterGameplayCue::OnOverlapBegin);
}

void AWaterGameplayCue::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGasCharacterBase* CS = Cast<AGasCharacterBase>(OtherActor);
	if (CS) {
		if (CS->GetAbilitySystemComponent())
		{
			UCharacterAbilitySystemComponent* AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(CS->GetAbilitySystemComponent());
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			
			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(WetEffect, CS->GetCharacterLevel(), EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			}
			
		}
	}
}

