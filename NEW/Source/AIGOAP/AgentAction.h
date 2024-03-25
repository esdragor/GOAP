 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumUtils.h"
#include "AgentAction.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable)
class AIGOAP_API UAgentAction : public UObject
{
	GENERATED_BODY()
public:
	TArray<EWorldStateEnum>* GetConditions();
	TArray<EWorldStateEnum>* GetResults();
	float GetCostTimer() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "AgentAction")
	void Execute(APawn * owner, float DeltaTime);
	bool IsFinished() const;
	void ResetByDefault();
	void StartTask(APawn * owner);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "AgentAction")
	void BP_StartTask(APawn * owner);

	
public:
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> conditions;
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> results;

protected:
	float costTimer;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EStateActionEnum currentStep = EStateActionEnum::NotStarted;
};
