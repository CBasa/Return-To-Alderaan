// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameStateBase_RJ.h"
#include "ReturnToAlderaanGameMode.generated.h"

UCLASS(minimalapi)
class AReturnToAlderaanGameMode : public AGameModeBase {
  GENERATED_BODY()

public:
  AReturnToAlderaanGameMode();

  virtual ~AReturnToAlderaanGameMode() = default;

  /** Return the Shield Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual float GetShieldAmount() const;

  /** Return the Max Shield Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual float GetMaxShield() const;

  /** Return the Shield Upgrade Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual int GetShieldUpgrades() const;

  /** Return the Shields per Upgrade Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual int GetShieldsPerUpgrade() const;

  /** Return the Warp Fuel Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual float GetWarpFuelAmount() const;

  /** Return the Max Warp Fuel Amount */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual float GetMaxWarpFuel() const;

  /** Return the Current Level */
  UFUNCTION(BlueprintPure, Category = "Game")
  virtual ELevelToLoad GetCurrentLevelEnum() const;

  /** Return if player has enough fuel to warp */
  UFUNCTION(BlueprintPure, Category = "Game")
  virtual bool CanWarp() const;

  /** Return the ShuttleDestroyedByBlackhole Flag */
  UFUNCTION(BlueprintPure, Category = "Health")
  virtual bool GetShuttleDestroyedByBlackhole() const;

  /** Return the MissionComplete Flag */
  UFUNCTION(BlueprintPure, Category = "Game")
  virtual bool GetMissionComplete() const;

  /** Return the SpeedBoostActive Flag */
  UFUNCTION(BlueprintPure, Category = "Fuel")
  virtual bool GetSpeedBoostActive() const;

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetShieldAmount(float NewShieldAmount);

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetMaxShield(float NewMaxShield);

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetShieldUpgrades(int NewShieldUpgrades);

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetShieldsPerUpgrade(int NewShieldsPerUpgrade);

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetWarpFuelAmount(float NewWarpFuelAmount);

  /** Set the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetMaxWarpFuel(float NewMaxWarpFuel);

  /** Set the Current Level */
  UFUNCTION(BlueprintCallable, Category = "Game")
  virtual void SetCurrentLevelEnum(ELevelToLoad NewCurrentLevel);

  /** Set the ShuttleDestroyedByBlackhole Flag */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void SetShuttleDestroyedByBlackhole(bool NewValue);

  /** Set the ShuttleDestroyedByBlackhole Flag */
  UFUNCTION(BlueprintCallable, Category = "Game")
  virtual void SetMissionComplete(bool NewValue);

  /** Set the SpeedBoostActive Flag */
  UFUNCTION(BlueprintCallable, Category = "Fuel")
  virtual void SetSpeedBoostActive(bool NewValue);

  /** Modify the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void ModifyShieldAmount(float amount);

  /** Modify the Shield Amount */
  UFUNCTION(BlueprintCallable, Category = "Health")
  virtual void ModifyWarpFuelAmount(float amount);

  /** Verify the Shield Amount */
  virtual void VerifyShieldAmount();

  /** Verify the Shield Amount */
  virtual void VerifyWarpFuelAmount();

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
  FVector spawnPoint;

  virtual void StartPlay();

  UFUNCTION(BlueprintNativeEvent, Category = "Health",
            DisplayName = "Start Play")
  void StartPlayEvent();
};
