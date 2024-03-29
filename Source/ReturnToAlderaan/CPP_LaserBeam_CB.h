// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_HealthAndAttackSystem_CB.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h" // Include the header for ProjectileMovementComponent
#include "Components/AudioComponent.h" 
#include "Sound/SoundBase.h"
#include "CPP_LaserBeam_CB.generated.h"

UCLASS()
class RETURNTOALDERAAN_API ACPP_LaserBeam_CB : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_LaserBeam_CB();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* LaserSprite; // Use UPaperSpriteComponent for the paper sprite

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Settings")
	float TimeToLive;

	FVector TargetLocation;



public:	
	UFUNCTION()
	virtual void OnLaserBeamOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
