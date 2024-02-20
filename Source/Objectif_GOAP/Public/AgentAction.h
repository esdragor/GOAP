// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumUtils.h"
#include "UObject/NoExportTypes.h"
#include "AgentAction.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable)
class OBJECTIF_GOAP_API UAgentAction : public UObject
{
	GENERATED_BODY()

public:
	TArray<EWorldStateEnum>* GetConditions();
	TArray<EWorldStateEnum>* GetResults();
	TArray<EGoalEnum>* GetGoals();
protected:
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> conditions;
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> results;
	UPROPERTY(EditAnywhere)
	TArray<EGoalEnum> goals;
private:
	
};
