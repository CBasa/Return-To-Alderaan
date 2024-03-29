// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyShipCharacter_CB.h"
#include "CPP_LaserBeam_CB.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "GameStateBase_RJ.h"

#include "Engine/World.h"

// Sets default values
ACPP_EnemyShipCharacter_CB::ACPP_EnemyShipCharacter_CB() {
  // Set this character to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticMeshComponent =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyShipMesh"));
  StaticMeshComponent->SetupAttachment(GetDefaultAttachComponent());

  // Set default values
  SplineComponent = nullptr; // Ensure SplineComponent is initialized to nullptr
  MovementSpeed = 1.0f;
  DistanceAlongSpline = 0.0f;
  MaxHealth = 100.0f;
}

// Called when the game starts or when spawned
void ACPP_EnemyShipCharacter_CB::BeginPlay() {
  Super::BeginPlay();
  CurrentHealth = MaxHealth;
  UE_LOG(LogTemp, Warning, TEXT("Enemy ship start health set in BP: %f"),
         MaxHealth);

  // Find spline component by tag or other means
  SplineComponent = FindComponentByClass<USplineComponent>();

  if (!SplineComponent) {
    UE_LOG(LogTemp, Warning, TEXT("Spline component not found!"));
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Spline component found!"));
  }
}

USplineComponent *ACPP_EnemyShipCharacter_CB::GetSplineComponent() {
  return SplineComponent;
}

// Called every frame
void ACPP_EnemyShipCharacter_CB::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  // if (SplineComponent)
  //{
  //     // Move along the spline based on the distance and speed
  //     DistanceAlongSpline += MovementSpeed * DeltaTime;

  //    // Get the location and tangent at the current distance along the spline
  //    FTransform Transform =
  //    SplineComponent->GetTransformAtDistanceAlongSpline(DistanceAlongSpline,
  //    ESplineCoordinateSpace::World); FVector Location =
  //    SplineComponent->GetLocationAtDistanceAlongSpline(DistanceAlongSpline,
  //    ESplineCoordinateSpace::World); FVector Tangent =
  //    SplineComponent->GetTangentAtDistanceAlongSpline(DistanceAlongSpline,
  //    ESplineCoordinateSpace::World);

  //    // Set the character's location and rotation
  //    //SetActorRelativeTransform(Transform);
  //    SetActorLocationAndRotation(Location, Tangent.Rotation());

  //    //Check if the character reached the end of the spline
  //    if (DistanceAlongSpline >= SplineComponent->GetSplineLength())
  //    {
  //        // Reset the distance along the spline for looping movement
  //        DistanceAlongSpline = 0.0f;
  //    }
  //}
}

// Called to bind functionality to input
void ACPP_EnemyShipCharacter_CB::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACPP_EnemyShipCharacter_CB::HealthDamage(float DamageAmount) {
  UE_LOG(LogTemp, Warning, TEXT("Enemy ship current health: %f"),
         CurrentHealth);
  if (IsBoss) {
    // Boss receives less damage than other enemy ships
    CurrentHealth -= BossHealthDamageFactor * DamageAmount;
  } else {
    CurrentHealth -= DamageAmount;
  }
  if (CurrentHealth <= 0.0f) {
    // Handle death
    Destroy();
    UE_LOG(LogTemp, Warning, TEXT("Enemy ship destroyed!"));

    if (IsBoss) {
      // Trigger display of the mission complete UI widget
      GetWorld()
          ->GetAuthGameMode()
          ->GetGameState<AGameStateBase_RJ>()
          ->MissionComplete = true;
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("Enemy ship damage taken: %f"), DamageAmount);
}

float ACPP_EnemyShipCharacter_CB::GetCurrentHealth() const {
  return CurrentHealth;
}

float ACPP_EnemyShipCharacter_CB::GetMaxHealth() const { return MaxHealth; }
