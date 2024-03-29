// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_BTTask_MoveAlongSpline_CB.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CPP_EnemyShipCharacter_CB.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UCPP_BTTask_MoveAlongSpline_CB::UCPP_BTTask_MoveAlongSpline_CB()
{
	NodeName = TEXT("Move Along Spline Path CPP");
}

EBTNodeResult::Type UCPP_BTTask_MoveAlongSpline_CB::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Retrieve the blackboard component
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // Get the AI controlled character
    ACPP_EnemyShipCharacter_CB* ControlledCharacter = Cast<ACPP_EnemyShipCharacter_CB>(OwnerComp.GetAIOwner()->GetPawn());
    if (!ControlledCharacter)
    {
        return EBTNodeResult::Failed;
    }

    // Retrieve spline component from the character blueprint
    SplineComponent = ControlledCharacter->GetSplineComponent();
    if (!SplineComponent)
    {
        return EBTNodeResult::Failed;
    }

    // Calculate distance along the spline
    float Distance = SplineComponent->GetSplineLength();
    FVector NextPosition = SplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::World);

    // Move the AI character along the spline
    ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = 600; // Set the movement speed
    ControlledCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking); // Ensure the character is in walking mode

    // Implement the loop to move along the spline
    float CurrentDistance = 0.0f;
    while (CurrentDistance < Distance)
    {
        // Calculate the direction to the next point on the spline
        FVector Direction = (NextPosition - ControlledCharacter->GetActorLocation()).GetSafeNormal();

        // Move the character towards the next point
        ControlledCharacter->AddMovementInput(Direction);

        // Update the current distance and get the next position
        CurrentDistance += FVector::Distance(ControlledCharacter->GetActorLocation(), NextPosition);
        NextPosition = SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World);

        // Update the blackboard if needed
        BlackboardComp->SetValueAsVector(BlackboardKey.SelectedKeyName, NextPosition);

        //UE_LOG(LogTemp, Warning, TEXT("Current distance: %f Spline Length: %f"), CurrentDistance, Distance);

        // Wait for a short time to update the movement
        //FPlatformProcess::Sleep(0.1f);
    }

    return EBTNodeResult::Succeeded;
}
