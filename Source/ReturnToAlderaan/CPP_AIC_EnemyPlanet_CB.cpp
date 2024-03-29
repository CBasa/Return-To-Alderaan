// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_AIC_EnemyPlanet_CB.h"
#include "BehaviorTree/BlackboardComponent.h"

ACPP_AIC_EnemyPlanet_CB::ACPP_AIC_EnemyPlanet_CB()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ACPP_AIC_EnemyPlanet_CB::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BehaviorTree)) {
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

void ACPP_AIC_EnemyPlanet_CB::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (IsValid(BehaviorTree) && IsValid(Blackboard)) {
		Blackboard->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	}
}
