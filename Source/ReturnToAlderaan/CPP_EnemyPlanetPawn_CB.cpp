// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyPlanetPawn_CB.h"

// Sets default values
ACPP_EnemyPlanetPawn_CB::ACPP_EnemyPlanetPawn_CB()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyPlanetMesh"));
	StaticMeshComponent->SetupAttachment(GetDefaultAttachComponent());
}

// Called when the game starts or when spawned
void ACPP_EnemyPlanetPawn_CB::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_EnemyPlanetPawn_CB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_EnemyPlanetPawn_CB::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

