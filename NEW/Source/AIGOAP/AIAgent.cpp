// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAgent.h"

#include "PlannerUtils.h"

// Sets default values
AAIAgent::AAIAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIAgent::NeedToSetupPlan()
{
	// currentActions = UPlannerUtils::MakePlanActions(allActions, &worldState, &goals);
	UE_LOG(LogTemp, Warning, TEXT("nb of actions: %d"), currentActions.Num());
}

// Called every frame
void AAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

