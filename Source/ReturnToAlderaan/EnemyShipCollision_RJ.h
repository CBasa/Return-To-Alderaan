// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EnemyShipCollision_RJ.generated.h"

UCLASS()
class RETURNTOALDERAAN_API AEnemyShipCollision_RJ : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AEnemyShipCollision_RJ();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditAnywhere, Category = "Health")
  float CollisionRadius{250.F};

  UPROPERTY(VisibleAnywhere, Category = "Health")
  float Health{100.F};

  UPROPERTY(VisibleAnywhere, Category = "Health")
  float HitDamage{10.F};

  UPROPERTY(VisibleAnywhere, Category = "Collision")
  class USphereComponent *Sphere1;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                      class AActor *OtherActor,
                      class UPrimitiveComponent *OtherComp,
                      int32 OtherBodyIndex, bool bFromSweep,
                      const FHitResult &SweepResult);

  UFUNCTION()
  void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                    class AActor *OtherActor,
                    class UPrimitiveComponent *OtherComp,
                    int32 OtherBodyIndex) const;
};
