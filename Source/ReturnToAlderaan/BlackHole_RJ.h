// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BlackHole_RJ.generated.h"

UCLASS()
class RETURNTOALDERAAN_API ABlackHole_RJ : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ABlackHole_RJ();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  //  UPROPERTY(EditAnywhere, Category = "Ship Collision")
  //  class ASpaceShuttle_RJ *SpaceShuttle;

  UPROPERTY(VisibleAnywhere, Category = "Ship Collision")
  class USphereComponent *Sphere1;

  //  UPROPERTY(VisibleAnywhere, Category = "Ship Collision")
  //  bool DestroyedShip{false};

  UPROPERTY(EditAnywhere, Category = "Ship Collision")
  float CollisionRadius{500.F};

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                      class AActor *OtherActor,
                      class UPrimitiveComponent *OtherComp,
                      int32 OtherBodyIndex, bool bFromSweep,
                      const FHitResult &SweepResult);

  UFUNCTION()
  void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                    class AActor *OtherActor,
                    class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

  void AddForceToShip(float Value, AActor *CollidingSpaceShuttle);
};
