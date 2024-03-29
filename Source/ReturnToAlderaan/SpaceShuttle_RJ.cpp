// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShuttle_RJ.h"
#include "GameStateBase_RJ.h"

// #include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ASpaceShuttle_RJ::ASpaceShuttle_RJ() {
  //: Sphere1(CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"))) {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  //  Sphere1->InitSphereRadius(CollisionRadius);
  //  Sphere1->SetupAttachment(RootComponent);
  //  Sphere1->OnComponentBeginOverlap.AddDynamic(
  //      this, &ASpaceShuttle_RJ::OnOverlapBegin);
  //  Sphere1->OnComponentEndOverlap.AddDynamic(this,
  //                                          &ASpaceShuttle_RJ::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASpaceShuttle_RJ::BeginPlay() {
  Super::BeginPlay();

  //  DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionRadius, 50,
  //                FColor::Purple, true, -1, 0, 2);
}

// Called every frame
void ASpaceShuttle_RJ::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void ASpaceShuttle_RJ::SetupPlayerInputComponent(
    UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASpaceShuttle_RJ::OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                                      class AActor *OtherActor,
                                      class UPrimitiveComponent *OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult &SweepResult) {

  UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin: %s"), *OtherActor->GetName());

  if ((OtherActor != nullptr) && (OtherActor != this) &&
      (OtherComp != nullptr)) {
    // Health -= HitDamage;
  }
}

void ASpaceShuttle_RJ::OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                                    class AActor *OtherActor,
                                    class UPrimitiveComponent *OtherComp,
                                    int32 OtherBodyIndex) {}

void ASpaceShuttle_RJ::HealthDamage(float DamageAmount) {
  GetWorld()
      ->GetAuthGameMode()
      ->GetGameState<AGameStateBase_RJ>()
      ->ShieldAmount -= DamageAmount;
}

float ASpaceShuttle_RJ::GetCurrentHealth() const {
  return GetWorld()
      ->GetAuthGameMode()
      ->GetGameState<AGameStateBase_RJ>()
      ->ShieldAmount;
}

float ASpaceShuttle_RJ::GetMaxHealth() const {
  return GetWorld()
      ->GetAuthGameMode()
      ->GetGameState<AGameStateBase_RJ>()
      ->MaxShield;
}

void ASpaceShuttle_RJ::MoveToLocation(FVector NewLocation) {
  SetActorLocation(NewLocation);
}
