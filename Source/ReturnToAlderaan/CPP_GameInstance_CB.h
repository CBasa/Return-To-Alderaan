// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReturnToAlderaanGameMode.h"
#include "CPP_GameInstance_CB.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOALDERAAN_API UCPP_GameInstance_CB : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game")
	ELevelToLoad CurrentLevelEnum;
	
};
