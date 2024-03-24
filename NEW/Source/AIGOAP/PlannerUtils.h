// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlannerUtils.generated.h"

/**
 * 
 */
UCLASS()
class AIGOAP_API UPlannerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TArray<TSubclassOf<UAgentAction>> MakePlanActions(TArray<TSubclassOf<UAgentAction>> allActions, TArray<EWorldStateEnum>* worldState, TArray<EWorldStateEnum>* goals);
private:

	static bool TryBuildTreeAction(TArray<TSubclassOf<UAgentAction>> allActions,
	TArray<EWorldStateEnum>* worldState, EWorldStateEnum goal, TArray<TSubclassOf<UAgentAction>>& branch);
	static bool TryCreateBranchAction(TArray<TSubclassOf<UAgentAction>> allActions,
		TArray<EWorldStateEnum>* worldState,
		TArray<EWorldStateEnum>* conditions, TArray<TSubclassOf<UAgentAction>>* branch, float maxCost);
	static float GetBranchCost(TArray<TSubclassOf<UAgentAction>> actions);
};
