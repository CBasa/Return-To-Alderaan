// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_HealthAndAttackSystem_CB.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_HealthAndAttackSystem_CB : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RETURNTOALDERAAN_API ICPP_HealthAndAttackSystem_CB
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void HealthDamage(float DamageAmount) = 0;
	virtual float GetCurrentHealth() const = 0;
	virtual float GetMaxHealth() const = 0;

};
