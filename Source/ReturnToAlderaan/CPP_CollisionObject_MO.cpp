// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CollisionObject_MO.h"

// Sets default values
ACPP_CollisionObject_MO::ACPP_CollisionObject_MO()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_CollisionObject_MO::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CollisionObject_MO::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

