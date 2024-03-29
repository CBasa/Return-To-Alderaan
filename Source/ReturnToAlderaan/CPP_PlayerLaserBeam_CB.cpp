// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerLaserBeam_CB.h"
#include "ReturnToAlderaanCharacter.h"


void ACPP_PlayerLaserBeam_CB::OnLaserBeamOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapped actor implements the HealthAndAttackInterface
	ICPP_HealthAndAttackSystem_CB* Interface = Cast<ICPP_HealthAndAttackSystem_CB>(OtherActor);

	// Check if the overlapped actor is the player
	AReturnToAlderaanCharacter* Player = Cast<AReturnToAlderaanCharacter>(OtherActor);
	
	if (Player) {
		UE_LOG(LogTemp, Warning, TEXT("player laser beam overlapping player"));
	}
	if (Interface && !Player)
	{

		// Apply damage to the overlapped actor
		Interface->HealthDamage(DamageAmount);
		// Destroy the laser beam after collision
		Destroy();
	}
}
