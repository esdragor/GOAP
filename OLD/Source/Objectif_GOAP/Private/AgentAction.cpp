// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentAction.h"

// TArray<EWorldStateEnum> UAgentAction::GetConditionsPure()
// {
// 	TArray<EWorldStateEnum> conditionsPure;
// 	UE_LOG(LogTemp, Warning, TEXT("GetConditionsPureCPP"));
// 	return conditionsPure;
// }

TArray<EWorldStateEnum>* UAgentAction::GetConditions()
{
	return &conditions;
}

TArray<EWorldStateEnum>* UAgentAction::GetResults()
{
	return &results;
}

TArray<EGoalEnum>* UAgentAction::GetGoals()
{
	return &goals;
}
