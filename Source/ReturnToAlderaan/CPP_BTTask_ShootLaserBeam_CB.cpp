// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTTask_ShootLaserBeam_CB.h"
#include "CPP_EnemyShipCharacter_CB.h"
#include "CPP_EnemyPlanetPawn_CB.h"
#include "CPP_LaserBeam_CB.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>

UCPP_BTTask_ShootLaserBeam_CB::UCPP_BTTask_ShootLaserBeam_CB()
{
	NodeName = TEXT("Shoot Laser Beams");

    // Set the audio component to play on startup
    //AudioComponent->bAutoActivate = false;

    //AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

    // Set default sound
    static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("/Script/Engine.SoundWave'/Game/AI/LaserBeam/A_Laser_CB.A_Laser_CB'"));
    if (SoundAsset.Succeeded())
    {
        SoundToPlay = SoundAsset.Object;
    }
}

EBTNodeResult::Type UCPP_BTTask_ShootLaserBeam_CB::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // Get the blackboard component
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Get the AI controller and its pawn
    AAIController* Controller = OwnerComp.GetAIOwner();
    if (!Controller)
    {
        return EBTNodeResult::Failed;
    }
    APawn* Pawn = Controller->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    // Get the actor's location and forward vector
    FVector ActorLocation = Pawn->GetActorLocation();
    FVector ActorForwardVector = Pawn->GetActorForwardVector();
    // Calculate the spawn position
    FVector SpawnPosition = ActorLocation + ActorForwardVector * SpawnDistance;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = Pawn;
    //SpawnParams.Instigator = Pawn->Instigator;

    ACPP_EnemyShipCharacter_CB* Ship = Cast<ACPP_EnemyShipCharacter_CB>(Pawn);
    ACPP_EnemyPlanetPawn_CB* Planet = Cast<ACPP_EnemyPlanetPawn_CB>(Pawn);
    if (Ship || Planet)
    {
        TSubclassOf<ACPP_LaserBeam_CB> BP_LaserBeam;
        if (Ship) {
            BP_LaserBeam = Ship->BP_LaserBeam;
            ACPP_LaserBeam_CB* LaserBeam = OwnerComp.GetWorld()->SpawnActor<ACPP_LaserBeam_CB>(BP_LaserBeam, SpawnPosition, Pawn->GetActorRotation(), SpawnParams);
            
            //Play laser sound
            if (LaserBeam) {
                UGameplayStatics::PlaySoundAtLocation(LaserBeam, SoundToPlay, LaserBeam->GetActorLocation(), VolumeMultiplier, PitchMultiplier);
            } else  {
                return EBTNodeResult::Failed;
            }
        }
        else if (Planet) {
            BP_LaserBeam = Planet->BP_LaserBeam;
            //Update spawn rotation to face towards player direction
            // Retrieve the player's location from the blackboard
            FVector PlayerLocation = BlackboardComp->GetValueAsVector(BlackboardKey.SelectedKeyName);

            // Calculate the rotation from the laser beam spawn point to the player's location
            FRotator LaserBeamRotation = (PlayerLocation - Pawn->GetActorLocation()).Rotation();

            ACPP_LaserBeam_CB* LaserBeam = OwnerComp.GetWorld()->SpawnActor<ACPP_LaserBeam_CB>(BP_LaserBeam, SpawnPosition, LaserBeamRotation, SpawnParams);
            
            //Play laser sound
            if (LaserBeam) {
                UGameplayStatics::PlaySoundAtLocation(LaserBeam, SoundToPlay, LaserBeam->GetActorLocation(), VolumeMultiplier, PitchMultiplier);
            }
            else {
                return EBTNodeResult::Failed;
            }
        }
        
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Pawn class cannot shoot"));
    }

    return EBTNodeResult::Succeeded;
}
