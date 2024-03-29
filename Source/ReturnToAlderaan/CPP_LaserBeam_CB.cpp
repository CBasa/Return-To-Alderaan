// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_LaserBeam_CB.h"

// Sets default values
ACPP_LaserBeam_CB::ACPP_LaserBeam_CB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the root scene component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent; // Set the root component

	
	LaserSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LaserSprite")); // Create a UPaperSpriteComponent
	LaserSprite->SetupAttachment(RootSceneComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent")); // Create a UArrowComponent
	ArrowComponent->SetupAttachment(RootSceneComponent); // Attach the arrow component to the root component

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent")); // Create a UBoxComponent for collision
	CollisionComponent->SetupAttachment(RootSceneComponent); // Attach the collision component to the root component

	TimeToLive = 3.0f; // Time in seconds before the laser beam destroys itself
	DamageAmount = 2.0f; // Amount of damage laser does to other actor implementing health and attack interface
}

// Called when the game starts or when spawned
void ACPP_LaserBeam_CB::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(TimeToLive);

	// Set collision settings
	if (CollisionComponent) {
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // Set to query only
		CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap); // Allow overlap with all channels
		CollisionComponent->SetGenerateOverlapEvents(true); // Generate overlap events

		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPP_LaserBeam_CB::OnLaserBeamOverlap); // Bind the overlap event
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No collision component"));
	}
}


void ACPP_LaserBeam_CB::OnLaserBeamOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor implements the HealthAndAttackInterface
	ICPP_HealthAndAttackSystem_CB* Interface = Cast<ICPP_HealthAndAttackSystem_CB>(OtherActor);
	if (Interface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Laser beam overlapping interface object"));

		// Apply damage to the overlapped actor
		Interface->HealthDamage(DamageAmount);
		// Destroy the laser beam after collision
		Destroy();
	}

	
}

// Called every frame
void ACPP_LaserBeam_CB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

