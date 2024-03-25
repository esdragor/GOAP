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

float UAgentAction::GetCostTimer() const
{
	return costTimer;
}

bool UAgentAction::IsFinished() const
{
	return currentStep == EStateActionEnum::Finished;
}

void UAgentAction::ResetByDefault()
{
	currentStep = EStateActionEnum::NotStarted;
}

void UAgentAction::StartTask(APawn * owner)
{
	currentStep = EStateActionEnum::InProgress;
	BP_StartTask(owner);
}
