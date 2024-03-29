// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReturnToAlderaanGameMode.h"
#include "GameStateBase_RJ.h"
#include "ReturnToAlderaanCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Engine/World.h"

AReturnToAlderaanGameMode::AReturnToAlderaanGameMode() {
  // set default pawn class to our Blueprinted character
  static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
      TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
  if (PlayerPawnBPClass.Class != NULL) {
    DefaultPawnClass = PlayerPawnBPClass.Class;
  }

  GameStateClass = AGameStateBase_RJ::StaticClass();
}

float AReturnToAlderaanGameMode::GetShieldAmount() const {
  return GetGameState<AGameStateBase_RJ>()->ShieldAmount;
}

float AReturnToAlderaanGameMode::GetMaxShield() const {
  return GetGameState<AGameStateBase_RJ>()->MaxShield;
}

int AReturnToAlderaanGameMode::GetShieldUpgrades() const {
  return GetGameState<AGameStateBase_RJ>()->ShieldUpgrades;
}

int AReturnToAlderaanGameMode::GetShieldsPerUpgrade() const {
  return GetGameState<AGameStateBase_RJ>()->ShieldsPerUpgrade;
}

float AReturnToAlderaanGameMode::GetWarpFuelAmount() const {
  return GetGameState<AGameStateBase_RJ>()->WarpFuelAmount;
}

float AReturnToAlderaanGameMode::GetMaxWarpFuel() const {
  return GetGameState<AGameStateBase_RJ>()->MaxWarpFuel;
}

ELevelToLoad AReturnToAlderaanGameMode::GetCurrentLevelEnum() const
{
    return GetGameState<AGameStateBase_RJ>()->CurrentLevelEnum;
}

bool AReturnToAlderaanGameMode::CanWarp() const
{
    return GetWarpFuelAmount() >= GetMaxWarpFuel();
}

bool AReturnToAlderaanGameMode::GetShuttleDestroyedByBlackhole() const {
  return GetGameState<AGameStateBase_RJ>()->ShuttleDestroyedByBlackhole;
}

bool AReturnToAlderaanGameMode::GetMissionComplete() const {
  return GetGameState<AGameStateBase_RJ>()->MissionComplete;
}

bool AReturnToAlderaanGameMode::GetSpeedBoostActive() const {
  return GetGameState<AGameStateBase_RJ>()->SpeedBoostActive;
}

void AReturnToAlderaanGameMode::SetShieldAmount(float NewShieldAmount) {
  GetGameState<AGameStateBase_RJ>()->ShieldAmount = NewShieldAmount;
  VerifyShieldAmount();
}

void AReturnToAlderaanGameMode::SetMaxShield(float NewMaxShield) {
  GetGameState<AGameStateBase_RJ>()->MaxShield = NewMaxShield;
}

void AReturnToAlderaanGameMode::SetShieldUpgrades(int NewShieldUpgrades) {
  GetGameState<AGameStateBase_RJ>()->ShieldUpgrades = NewShieldUpgrades;
  ModifyShieldAmount(GetGameState<AGameStateBase_RJ>()->ShieldsPerUpgrade);
}

void AReturnToAlderaanGameMode::SetShieldsPerUpgrade(int NewShieldsPerUpgrade) {
  GetGameState<AGameStateBase_RJ>()->ShieldsPerUpgrade = NewShieldsPerUpgrade;
}

void AReturnToAlderaanGameMode::SetWarpFuelAmount(float NewWarpFuelAmount) {
  GetGameState<AGameStateBase_RJ>()->WarpFuelAmount = NewWarpFuelAmount;
  VerifyWarpFuelAmount();
}

void AReturnToAlderaanGameMode::SetMaxWarpFuel(float NewMaxWarpFuel) {
  GetGameState<AGameStateBase_RJ>()->MaxWarpFuel = NewMaxWarpFuel;
}

void AReturnToAlderaanGameMode::SetCurrentLevelEnum(ELevelToLoad NewCurrentLevel)
{
    GetGameState<AGameStateBase_RJ>()->CurrentLevelEnum = NewCurrentLevel;
}

void AReturnToAlderaanGameMode::SetShuttleDestroyedByBlackhole(bool NewValue) {
  GetGameState<AGameStateBase_RJ>()->ShuttleDestroyedByBlackhole = NewValue;
}

void AReturnToAlderaanGameMode::SetMissionComplete(bool NewValue) {
  GetGameState<AGameStateBase_RJ>()->MissionComplete = NewValue;
}

void AReturnToAlderaanGameMode::SetSpeedBoostActive(bool NewValue) {
  GetGameState<AGameStateBase_RJ>()->SpeedBoostActive = NewValue;
}

void AReturnToAlderaanGameMode::ModifyShieldAmount(float amount) {
  GetGameState<AGameStateBase_RJ>()->ShieldAmount += amount;
  VerifyShieldAmount();
}

void AReturnToAlderaanGameMode::ModifyWarpFuelAmount(float amount) {
  GetGameState<AGameStateBase_RJ>()->WarpFuelAmount += amount;
  VerifyWarpFuelAmount();
}

void AReturnToAlderaanGameMode::VerifyShieldAmount() {
  AGameStateBase_RJ *gameState = GetGameState<AGameStateBase_RJ>();
  if (gameState->ShieldAmount >
      (gameState->MaxShield +
       gameState->ShieldUpgrades * gameState->ShieldsPerUpgrade)) {
    gameState->ShieldAmount =
        gameState->MaxShield +
        gameState->ShieldUpgrades * gameState->ShieldsPerUpgrade;
  } else if (gameState->ShieldAmount < 0) {
    gameState->ShieldAmount = 0;
  }
}

void AReturnToAlderaanGameMode::VerifyWarpFuelAmount() {
  if (GetGameState<AGameStateBase_RJ>()->WarpFuelAmount >
      GetGameState<AGameStateBase_RJ>()->MaxWarpFuel) {
    GetGameState<AGameStateBase_RJ>()->WarpFuelAmount =
        GetGameState<AGameStateBase_RJ>()->MaxWarpFuel;
  } else if (GetGameState<AGameStateBase_RJ>()->WarpFuelAmount < 0) {
    GetGameState<AGameStateBase_RJ>()->WarpFuelAmount = 0;
  }
}

void AReturnToAlderaanGameMode::StartPlay() {
  //  GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Red,
  //                                   TEXT("Start Play called"));
  StartPlayEvent();

  /* Initialise stuff here */
  GetWorld()
      ->GetAuthGameMode()
      ->GetGameState<AGameStateBase_RJ>()
      ->ShieldAmount = 100.F;

  Super::StartPlay();
}

void AReturnToAlderaanGameMode::StartPlayEvent_Implementation() {
  //  GEngine->AddOnScreenDebugMessage(
  //      -1, 5.F, FColor::Red,
  //      TEXT("StartPlayEvent Default Implementation called"));
}
