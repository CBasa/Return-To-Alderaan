// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CPP_HealthAndAttackSystem_CB.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "SpaceShuttle_RJ.generated.h"

UCLASS()
class RETURNTOALDERAAN_API ASpaceShuttle_RJ
    : public APawn,
      public ICPP_HealthAndAttackSystem_CB {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ASpaceShuttle_RJ();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

  UPROPERTY(EditAnywhere, Category = "Health")
  float CollisionRadius{250.F};

  UPROPERTY(VisibleAnywhere, Category = "Health")
  float Health{100.F};

  UPROPERTY(VisibleAnywhere, Category = "Health")
  float HitDamage{10.F};

  //  UPROPERTY(VisibleAnywhere, Category = "Collision")
  // class USphereComponent *Sphere1;

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

  virtual void HealthDamage(float DamageAmount) override;
  virtual float GetCurrentHealth() const override;
  virtual float GetMaxHealth() const override;

  void MoveToLocation(FVector NewLocation);
};
