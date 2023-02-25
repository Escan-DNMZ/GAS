// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerState.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"

AGASPlayerState::AGASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>("ASC");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>("ASB");
	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AGASPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AGASPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &AGASPlayerState::MaxHealthChanged);
		CharacterManaDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &AGASPlayerState::ManaChanged);
		CharacterMaxManaDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &AGASPlayerState::MaxManaChanged);
		CharacterLevelDelegate = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &AGASPlayerState::CharacterLevelChanged);
	
		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AGASPlayerState::StunTagChanged);
	}
}


UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* AGASPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool AGASPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;;
}

void AGASPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	// TODO -- implement HUD
}

float AGASPlayerState::GetHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AGASPlayerState::GetMaxHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AGASPlayerState::GetMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AGASPlayerState::GetMaxMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

int32 AGASPlayerState::GetCharacterLevel() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetLevel();
	}
	return 0;
}

void AGASPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{

}

void AGASPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void AGASPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
}

void AGASPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
}

void AGASPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
}

void AGASPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;

		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);

	}
}
