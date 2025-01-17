// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

#include "PlannerUtils.h"

// Sets default values
AAgent::AAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	currentActions = UPlannerUtils::MakePlanActions(allActions, &worldState, &goals);
	UE_LOG(LogTemp, Warning, TEXT("nb of actions: %d"), currentActions.Num());
}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

