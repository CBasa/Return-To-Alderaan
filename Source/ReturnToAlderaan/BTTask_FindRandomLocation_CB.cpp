// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation_CB.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindRandomLocation_CB::UBTTask_FindRandomLocation_CB()
{
	NodeName = TEXT("Find Random Location CPP");
}

EBTNodeResult::Type UBTTask_FindRandomLocation_CB::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Finding Random Location"));

	FNavLocation Location;
	AAIController* AIController = OwnerComp.GetAIOwner();

	const APawn* AIPawn = AIController->GetPawn();
	const FVector Origin = AIPawn->GetActorLocation();
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	//Find a random point to navigate to and add it to blackboard
	if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(Origin, SearchRadius, Location)) {
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
