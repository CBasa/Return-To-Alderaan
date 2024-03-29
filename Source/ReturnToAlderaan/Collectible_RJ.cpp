// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible_RJ.h"
#include "GameStateBase_RJ.h"
#include "ReturnToAlderaanGameMode.h"
#include "SpaceShuttle_RJ.h"

#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ACollectible_RJ::ACollectible_RJ()
    : Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))) {
  // Set this actor to call Tick() every frame.  You can turn this off to
  // improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Sphere1->InitSphereRadius(CollisionRadius);
  Sphere1->SetupAttachment(RootComponent);
  Sphere1->OnComponentBeginOverlap.AddDynamic(this,
                                              &ACollectible_RJ::OnOverlapBegin);
  // Sphere1->OnComponentEndOverlap.AddDynamic(this,
  // &ACollectible_RJ::OnOverlapEnd);
}

void ACollectible_RJ::CollectThis() {
  switch (pickupType) {
  case Pickups::SHIELD_UPGRADE:
    PickupShieldUpgrade();
    break;
  case Pickups::SHIELD_PICKUP:
    PickupShield();
    break;
  case Pickups::FUEL_PICKUP:
    PickupFuel();
    break;
  case Pickups::SPEED_BOOST:
    PickupSpeedBoost();
    break;
  }
  Destroy();
}

void ACollectible_RJ::PickupShieldUpgrade() {
  AReturnToAlderaanGameMode *gameMode =
      Cast<AReturnToAlderaanGameMode>(GetWorld()->GetAuthGameMode());
  gameMode->SetShieldUpgrades(gameMode->GetShieldUpgrades() + 1);
}

void ACollectible_RJ::PickupShield() {
  AReturnToAlderaanGameMode *gameMode =
      Cast<AReturnToAlderaanGameMode>(GetWorld()->GetAuthGameMode());
  gameMode->ModifyShieldAmount(amount);
}

void ACollectible_RJ::PickupFuel() {
  AReturnToAlderaanGameMode *gameMode =
      Cast<AReturnToAlderaanGameMode>(GetWorld()->GetAuthGameMode());
  gameMode->ModifyWarpFuelAmount(amount);
}

void ACollectible_RJ::PickupSpeedBoost() {
  GetWorld()
      ->GetAuthGameMode()
      ->GetGameState<AGameStateBase_RJ>()
      ->SpeedBoostActive = true;
}

// Called when the game starts or when spawned
void ACollectible_RJ::BeginPlay() {
  Super::BeginPlay();

  //  DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionRadius, 50,
  //                  FColor::Purple, true, -1, 0, 2);
}

// Called every frame
void ACollectible_RJ::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ACollectible_RJ::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                                     class AActor *OtherActor,
                                     class UPrimitiveComponent *OtherComp,
                                     int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult &SweepResult) {

  UE_LOG(LogTemp, Warning, TEXT("Collectible OnOverlapBegin: %s"),
         *OtherActor->GetName());

  if ((OtherActor != nullptr) && (OtherActor != this)) {
    auto *const OtherCompAsSpaceShuttle = Cast<ASpaceShuttle_RJ>(OtherActor);
    if (OtherCompAsSpaceShuttle != nullptr) {
      CollectThis();
    }
  }
}
