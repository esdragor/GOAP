// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentAction.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlannerUtils.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTIF_GOAP_API UPlannerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TArray<TSubclassOf<UAgentAction>*> MakePlanActions(TArray<TSubclassOf<UAgentAction>*>* allActions, TArray<EWorldStateEnum>* worldState, TArray<EGoalEnum>* goals);
private:
	static bool TryAddingActionWithDesiredGoal(TArray<TSubclassOf<UAgentAction>*>* allActions, TArray<EWorldStateEnum>* worldState, TArray<EWorldStateEnum> *goals, TArray<TSubclassOf<UAgentAction>*>& actions);
	static bool TryBuildTreeAction(TArray<TSubclassOf<UAgentAction>*>* allActions, TArray<EWorldStateEnum>* worldState, EGoalEnum goal, TArray<TSubclassOf<UAgentAction>*>& tree);
	static bool CheckAutoSuficentCondition(TSubclassOf<UAgentAction> *currentAction, TArray<EWorldStateEnum> *worldState);

private:
	static TArray<TArray<TSubclassOf<UAgentAction>*>*> *allBranches;
};
