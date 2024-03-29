// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole_RJ.h"
#include "GameStateBase_RJ.h"
#include "ReturnToAlderaanCharacter.h"
#include "SpaceShuttle_RJ.h"

#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include <string>

// Sets default values
ABlackHole_RJ::ABlackHole_RJ()
    : Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))) {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Sphere1->InitSphereRadius(CollisionRadius);
  Sphere1->SetupAttachment(RootComponent);
  Sphere1->OnComponentBeginOverlap.AddDynamic(this,
                                              &ABlackHole_RJ::OnOverlapBegin);
  Sphere1->OnComponentEndOverlap.AddDynamic(this, &ABlackHole_RJ::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABlackHole_RJ::BeginPlay() {
  Super::BeginPlay();

  //  DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionRadius, 50,
  //                  FColor::Purple, true, -1, 0, 2);
}

// Called every frame
void ABlackHole_RJ::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ABlackHole_RJ::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                                   class AActor *OtherActor,
                                   class UPrimitiveComponent *OtherComp,
                                   int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult &SweepResult) {

  if ((OtherActor != nullptr) && (OtherActor != this)) {
    auto *const OtherCompAsSpaceShuttle = Cast<ASpaceShuttle_RJ>(OtherActor);
    if (OtherCompAsSpaceShuttle != nullptr) {

      // deduct health - not set to zero, so the game over widget is not
      // automatically triggered, allowing the blackhole widget to be displayed,
      // explaining the shuttle got too close to the black hole.  Dismissing
      // that widget should reduce health to zero, to trigger automatic display
      // of game over widget
      GetWorld()
          ->GetAuthGameMode()
          ->GetGameState<AGameStateBase_RJ>()
          ->ShieldAmount = 1.F;

      // check health - for debugging only - delete after
      const float NewHealth{GetWorld()
                                ->GetAuthGameMode()
                                ->GetGameState<AGameStateBase_RJ>()
                                ->ShieldAmount};
      UE_LOG(LogTemp, Warning, TEXT("New health level: %f"), NewHealth);

      // inform player they hit a blackhole
      GetWorld()
          ->GetAuthGameMode()
          ->GetGameState<AGameStateBase_RJ>()
          ->ShuttleDestroyedByBlackhole = true;
    }
  }
}

void ABlackHole_RJ::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                                 class AActor *OtherActor,
                                 class UPrimitiveComponent *OtherComp,
                                 int32 OtherBodyIndex) {}

// void ABlackHole_RJ::AddForceToShip(float Value, AActor
// *CollidingSpaceShuttle) {
//   UE_LOG(LogTemp, Warning, TEXT("InAddForce 000"));
//   // auto *const SpaceShuttleActor = Cast<>(SpaceShuttle);
//   //  if (SpaceShuttle == nullptr) {
//   //
//   //    UE_LOG(LogTemp, Warning, TEXT("Shuttle is nullptr"));
//   //  }
//   if (Value > 0.F && CollidingSpaceShuttle != nullptr) {
//     UE_LOG(LogTemp, Warning, TEXT("InAddForce 001"));
//     UPrimitiveComponent *SpaceShuttleComponent =
//         CollidingSpaceShuttle->FindComponentByClass<UPrimitiveComponent>();
//     FVector ForceVector = GetActorForwardVector() * -99999.0F * Value;
//
//     if ((SpaceShuttleComponent != nullptr &&
//          SpaceShuttleComponent->IsSimulatingPhysics())) {
//       UE_LOG(LogTemp, Warning, TEXT("InAddForce 002"));
//       //  SpaceShuttleComponent->AddForce(ForceVector);
//     }
//     GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red,
//                                      GetActorForwardVector().ToString());
//   }
// }
