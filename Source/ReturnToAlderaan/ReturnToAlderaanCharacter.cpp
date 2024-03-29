// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReturnToAlderaanCharacter.h"
#include "ReturnToAlderaanGameMode.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AReturnToAlderaanCharacter

AReturnToAlderaanCharacter::AReturnToAlderaanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AReturnToAlderaanCharacter::HealthDamage(float DamageAmount)
{
	UWorld* World = GetWorld();
	AReturnToAlderaanGameMode* CurrentGameMode = Cast<AReturnToAlderaanGameMode>(World->GetAuthGameMode());

	if (CurrentGameMode) {

		float CurrentShield = CurrentGameMode->GetShieldAmount();
		UE_LOG(LogTemp, Warning, TEXT("Player current Shield: %f"), CurrentShield);
		CurrentShield -= DamageAmount;
		if (CurrentShield <= 0.0f) {
			// Handle death
			CurrentShield = 0.0f;
			CurrentGameMode->SetShieldAmount(CurrentShield);
			UE_LOG(LogTemp, Warning, TEXT("Player shields are at zero - GAME OVER"));
		}
		CurrentGameMode->SetShieldAmount(CurrentShield);
		UE_LOG(LogTemp, Warning, TEXT("Player damage taken: %f"), DamageAmount);
	}
}

float AReturnToAlderaanCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

float AReturnToAlderaanCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

void AReturnToAlderaanCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Player max health set in BP: %f"), MaxHealth);

	//Update max and current shield in game state
	UWorld* World = GetWorld();
	AReturnToAlderaanGameMode* CurrentGameMode = Cast<AReturnToAlderaanGameMode>(World->GetAuthGameMode());
	if (CurrentGameMode) {
		CurrentGameMode->SetMaxShield(MaxHealth);
		CurrentGameMode->SetShieldAmount(CurrentHealth);
		UE_LOG(LogTemp, Warning, TEXT("Player start current Shield: %f"), CurrentGameMode->GetShieldAmount());
		UE_LOG(LogTemp, Warning, TEXT("Player start max Shield: %f"), CurrentGameMode->GetMaxShield());
	}
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AReturnToAlderaanCharacter::SetLevel(FName LevelName, UCPP_GameInstance_CB* GameInstance, AReturnToAlderaanGameMode* GameMode, ELevelToLoad NewCurrentLevel)
{
	if (GameMode->CanWarp()) {
		FString LevelEnumString = UEnum::GetValueAsString(NewCurrentLevel);
		UE_LOG(LogTemp, Warning, TEXT("Warping to level %s"), *LevelEnumString);
		UGameplayStatics::OpenLevel(GetWorld(), LevelName);

		//Save current level in game instance so value persists between level changes
		GameInstance->CurrentLevelEnum = NewCurrentLevel;
		GameMode->SetWarpFuelAmount(0.0f);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AReturnToAlderaanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AReturnToAlderaanCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AReturnToAlderaanCharacter::Look);
	
		// Warping
		EnhancedInputComponent->BindAction(WarpAction, ETriggerEvent::Triggered, this, &AReturnToAlderaanCharacter::Warp);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AReturnToAlderaanCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AReturnToAlderaanCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AReturnToAlderaanCharacter::Warp(const FInputActionValue& Value)
{
	UWorld* World = GetWorld();
	AReturnToAlderaanGameMode* GameMode = Cast<AReturnToAlderaanGameMode>(World->GetAuthGameMode());
	UCPP_GameInstance_CB* GameInstance = Cast<UCPP_GameInstance_CB>(GetGameInstance());

	if (GameInstance && GameMode) {
		switch (GameInstance->CurrentLevelEnum) {
		case ELevelToLoad::StartLevel:
			UE_LOG(LogTemp, Warning, TEXT("You are on level 1, next level is: 2"));
			SetLevel(TEXT("Map_Level2_MO_RJ"), GameInstance, GameMode, ELevelToLoad::Level2);
			break;
		case ELevelToLoad::Level2:
			UE_LOG(LogTemp, Warning, TEXT("You are on level 2, next level is: 3"));
			SetLevel(TEXT("Map_Level3_MO_RJ"), GameInstance, GameMode, ELevelToLoad::Level3);
			break;
		case ELevelToLoad::Level3:
			UE_LOG(LogTemp, Warning, TEXT("You are on level 3, next level is: 4"));
			SetLevel(TEXT("Map_Level4_MO_RJ"), GameInstance, GameMode, ELevelToLoad::Level4);
			break;
		case ELevelToLoad::Level4:
			UE_LOG(LogTemp, Warning, TEXT("This is the final level"));
			//Do nothing - no more levels to warp to
			break;
		}
	}
}
