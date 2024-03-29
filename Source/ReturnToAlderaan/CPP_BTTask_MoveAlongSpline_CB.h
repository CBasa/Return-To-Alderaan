// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CPP_BTTask_MoveAlongSpline_CB.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOALDERAAN_API UCPP_BTTask_MoveAlongSpline_CB : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCPP_BTTask_MoveAlongSpline_CB();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // Speed of movement along the spline
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
    float MovementSpeed;

protected:
    // Pointer to the spline component
    class USplineComponent* SplineComponent;

    // Current distance along the spline
    float DistanceAlongSpline;

    
};
