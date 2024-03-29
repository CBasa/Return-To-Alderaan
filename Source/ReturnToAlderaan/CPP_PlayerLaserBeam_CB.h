// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_LaserBeam_CB.h"
#include "CPP_PlayerLaserBeam_CB.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOALDERAAN_API ACPP_PlayerLaserBeam_CB : public ACPP_LaserBeam_CB
{
	GENERATED_BODY()

	virtual void OnLaserBeamOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
