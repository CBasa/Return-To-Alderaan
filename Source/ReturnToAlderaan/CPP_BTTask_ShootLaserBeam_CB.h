// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Components/AudioComponent.h" 
#include "Sound/SoundBase.h"
#include "CPP_BTTask_ShootLaserBeam_CB.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOALDERAAN_API UCPP_BTTask_ShootLaserBeam_CB : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:
	UCPP_BTTask_ShootLaserBeam_CB();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
	float SpawnDistance = 200.0f;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(VisibleAnywhere, Category = "Laser Sound")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Laser Sound")
	USoundBase* SoundToPlay;

	UPROPERTY(EditAnywhere, Category = "Laser Sound")
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, Category = "Laser Sound")
	float PitchMultiplier;

};
