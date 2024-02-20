// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentAction.h"

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
