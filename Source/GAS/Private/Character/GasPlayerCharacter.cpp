// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GasPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Ai/GASAIController.h"
#include "Player/GASPlayerState.h"
#include "Player/GASPlayerController.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"


AGasPlayerCharacter::AGasPlayerCharacter(const class FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = AGASAIController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

void AGasPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGasPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AGasPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AGasPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGasPlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AGasPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGasPlayerCharacter::TurnRate);

	BindASCInput();
}

//Server Only
void AGasPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if (PS)
	{
		//Burda ise bu de�erleri suncuuya iletiyoruz.
		//Sunucu için ASC yi set 
		InitializeStartingValues(PS);

		AddStartupEffects();
		AddCharacterAbilities();
	
	}
}

USpringArmComponent* AGasPlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* AGasPlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float AGasPlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomLength;
}

FVector AGasPlayerCharacter::GetStartingLocation()
{
	return FVector();
}

FVector AGasPlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}

void AGasPlayerCharacter::BeginPlay()
{

	Super::BeginPlay();
	

	StartingCameraBoomLength = CameraBoom->TargetArmLength;
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

void AGasPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		
		AddControllerPitchInput(Value);
	}
}

void AGasPlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AGasPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void AGasPlayerCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void AGasPlayerCharacter::MoveForward(float Value)
{
	if (IsAlive())
	{
		FRotator Rotator = GetControlRotation();
		Rotator.Pitch = 0.0f;
		Rotator.Roll = 0.0f;

		AddMovementInput(Rotator.Vector(), Value);
	}
}

void AGasPlayerCharacter::MoveRight(float Value)
{
	if (IsAlive())
	{
		FRotator Rotator = GetControlRotation();
		Rotator.Pitch = 0.0f;
		Rotator.Roll = 0.0f;

		FVector GetRight = FRotationMatrix(Rotator).GetScaledAxis(EAxis::Y);

		AddMovementInput(GetRight, Value);
	}
}

//Client üzerinde çalışır Client daki bilgileri iletir
void AGasPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AGASPlayerState* PS = GetPlayerState<AGASPlayerState>();
	if (PS)
	{
		//Server'a Client bilgisini yollad�k , Server bunu PossesedBy da yapar
		InitializeStartingValues(PS);
		BindASCInput();
		
	}
}



/*
Eğer OnRep_PlayerState den çağırıldıysa Client'da bu değişiklikleri yapar
PossessedBy dan çağırırsanız Server için bu değişiklikleri yapar
*/
void AGasPlayerCharacter::InitializeStartingValues(AGASPlayerState* PS) {

	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());

	//AI'ın PlayerState'e erişememesi için bunu yapıyoruz
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	//Sahip olduğun karakter için can gibi değerleri bağlar
	AttributeSetBase = PS->GetAttributeSetBase();

	InitializeAttributes();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	SetHealth(GetMaxHealth());
	SetMana(GetMaxMana());

	AddStartupEffects();

	AddCharacterAbilities();
}
void AGasPlayerCharacter::BindASCInput()
{
	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(
			InputComponent,
			FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("GasAbilityId"),
				static_cast<int32>(GasAbilityId::Confirm),
				static_cast<int32>(GasAbilityId::Cancel)));

		ASCInputBound = true;
	}
}
