// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_HealthAndAttackSystem_CB.h"
#include "CPP_LaserBeam_CB.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "CPP_EnemyShipCharacter_CB.generated.h"

UCLASS()
class RETURNTOALDERAAN_API ACPP_EnemyShipCharacter_CB
    : public ACharacter,
      public ICPP_HealthAndAttackSystem_CB {
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  ACPP_EnemyShipCharacter_CB();

  USplineComponent *GetSplineComponent();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Static mesh component for the ship
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  class UStaticMeshComponent *StaticMeshComponent;

  // Default patrol path
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline Path")
  USplineComponent *SplineComponent;

  // Current distance along the spline
  float DistanceAlongSpline;

  // Speed of movement along the spline
  UPROPERTY(EditAnywhere, Category = "Spline Path")
  float MovementSpeed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
  float MaxHealth;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
  float CurrentHealth;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship")
  bool IsBoss{false};

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship")
  float BossHealthDamageFactor{0.5};

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

  virtual void HealthDamage(float DamageAmount) override;
  virtual float GetCurrentHealth() const override;
  virtual float GetMaxHealth() const override;

  // Set laser beam blueprint derived from cpp class
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Laser BP from CPP")
  TSubclassOf<ACPP_LaserBeam_CB> BP_LaserBeam;
};
