 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumUtils.h"
#include "AgentAction.generated.h"

/**
 * 
 */
UCLASS()
class AIGOAP_API UAgentAction : public UObject
{
	GENERATED_BODY()
public:
	TArray<EWorldStateEnum>* GetConditions();
	TArray<EWorldStateEnum>* GetResults();
	
public:
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> conditions;
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> results;

	//timer
	//execute()
};
