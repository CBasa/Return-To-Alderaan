// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTService_CanFollowPlayer_CB.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCPP_BTService_CanFollowPlayer_CB::UCPP_BTService_CanFollowPlayer_CB()
{
    NodeName = "Update Can Follow Player";
}

void UCPP_BTService_CanFollowPlayer_CB::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AAIController* AIController = OwnerComp.GetAIOwner();
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
    FVector AILocation = AIController->GetPawn()->GetActorLocation();

    float DistanceToPlayer = FVector::Distance(AILocation, PlayerLocation);

    // Get the blackboard component
    UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
    if (BlackboardComp)
    {
        // Update the blackboard key if the distance to the player is within the threshold
        if (DistanceToPlayer <= DistanceThreshold)
        {
            BlackboardComp->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
        }
        else
        {
            BlackboardComp->SetValueAsBool(BlackboardKey.SelectedKeyName, false);
        }
    }
}
