// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Collectible_RJ.generated.h"

UENUM(BlueprintType)
enum class Pickups : uint8 {
  SHIELD_UPGRADE UMETA(DisplayName = "Shield Upgrade"),
  SHIELD_PICKUP UMETA(DisplayName = "Shield Pickup"),
  FUEL_PICKUP UMETA(DisplayName = "Fuel Pickup"),
  SPEED_BOOST UMETA(DisplayName = "Speed Boost")
};

UCLASS()
class RETURNTOALDERAAN_API ACollectible_RJ : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ACollectible_RJ();

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
  Pickups pickupType;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
  int amount;

  UFUNCTION(BlueprintCallable)
  void CollectThis();

  void PickupShieldUpgrade();

  void PickupShield();

  void PickupFuel();

  void PickupSpeedBoost();

  UPROPERTY(VisibleAnywhere, Category = "Ship Collision")
  class USphereComponent *Sphere1;

  UPROPERTY(EditAnywhere, Category = "Ship Collision")
  float CollisionRadius{200.F};

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                      class AActor *OtherActor,
                      class UPrimitiveComponent *OtherComp,
                      int32 OtherBodyIndex, bool bFromSweep,
                      const FHitResult &SweepResult);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;
};
