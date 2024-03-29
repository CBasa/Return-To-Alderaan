// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyShipCollision_RJ.h"

#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemyShipCollision_RJ::AEnemyShipCollision_RJ()
    : Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))) {

  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Sphere1->InitSphereRadius(CollisionRadius);
  Sphere1->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyShipCollision_RJ::BeginPlay() {
  Super::BeginPlay();

  DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionRadius, 50,
                  FColor::Purple, true, -1, 0, 2);
}

// Called every frame
void AEnemyShipCollision_RJ::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AEnemyShipCollision_RJ::OnOverlapBegin(
    class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor,
    class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult &SweepResult) {
  if ((OtherActor != nullptr) && (OtherActor != this) &&
      (OtherComp != nullptr)) {
    Health -= HitDamage;
  }
}

void AEnemyShipCollision_RJ::OnOverlapEnd(
    class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor,
    class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex) const {}
