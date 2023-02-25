// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GameplatCues/AblazeGameplayCue.h"
#include "GameplayTagContainer.h"

AAblazeGameplayCue::AAblazeGameplayCue()
{
	Ablaze = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Debuff.Ablaze"));
	bAutoAttachToOwner = true;
	bAutoDestroyOnRemove = true;
}
