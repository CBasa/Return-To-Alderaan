// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CPP_BTService_CanFollowPlayer_CB.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOALDERAAN_API UCPP_BTService_CanFollowPlayer_CB : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UCPP_BTService_CanFollowPlayer_CB();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DistanceThreshold = 1000.0f;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
