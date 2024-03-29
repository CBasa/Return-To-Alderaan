// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameStateBase_RJ.generated.h"

/**
 *
 */

UENUM(BlueprintType)
enum class ELevelToLoad : uint8
{
	StartLevel UMETA(DisplayName = "Start Level"),
	Level2 UMETA(DisplayName = "Level 2"),
	Level3 UMETA(DisplayName = "Level 3"),
	Level4 UMETA(DisplayName = "Level 4")
	// Add more levels as needed
};

UCLASS()
class RETURNTOALDERAAN_API AGameStateBase_RJ : public AGameStateBase {
  GENERATED_BODY()

public:
  AGameStateBase_RJ();
  virtual ~AGameStateBase_RJ() = default;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
  float ShieldAmount{100.F};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
  float MaxShield{100.F};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
  int ShieldUpgrades{0};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
  int ShieldsPerUpgrade{20};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fuel")
  float WarpFuelAmount{0.F};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fuel")
  float MaxWarpFuel{0.F};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
  ELevelToLoad CurrentLevelEnum;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
  bool MissionComplete{false};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
  bool ShuttleDestroyedByBlackhole{false};

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fuel")
  bool SpeedBoostActive{false};
};
