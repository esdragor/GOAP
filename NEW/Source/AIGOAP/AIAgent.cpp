// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAgent.h"

#include "AgentAction.h"
#include "PlannerUtils.h"
#include "Kismet/GameplayStatics.h"

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
	NeedToSetupPlan();
	if (currentActions.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("current action: %s"), *currentActions[0]->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("no action"));
	}
}

void AAIAgent::NeedToSetupPlan()
{
	//TArray<TSubclassOf<UAgentAction>> PrefabsActions = UPlannerUtils::MakePlanActions(allActions, &worldState, &goals);
	TArray<TSubclassOf<UAgentAction>> tpt = UPlannerUtils::MakePlanActions(allActions, &worldState, &goals);
	currentActions.Empty();
	for (UClass* action : tpt)
	{
		UAgentAction* newTask = NewObject<UAgentAction>(GetTransientPackage(), action);
		currentActions.Add(newTask);
	}


	for (const auto action : currentActions)
	{
		action->ResetByDefault();
	}
	UE_LOG(LogTemp, Warning, TEXT("nb of actions: %d"), currentActions.Num());
	if (currentActions.Num() > 0)
		currentActions[0]->StartTask(this);
}

// Called every frame
void AAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (currentActions.Num() <= 0)
	{
		NeedToSetupPlan();
	}
	else
	{
		UAgentAction* action = currentActions[0];
		if (!action->IsFinished())
		{
			action->Execute(this, DeltaTime);
		}
		else
		{
			currentActions.RemoveAt(0);
			if (currentActions.Num() > 0)
				currentActions[0]->StartTask(this);
		}
	}
}

// Called to bind functionality to input

void AAIAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
