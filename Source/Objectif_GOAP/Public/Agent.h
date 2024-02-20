// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "AgentAction.h"
#include "AgentAction.h"
#include "EnumUtils.h"
#include "GameFramework/Character.h"
#include "Agent.generated.h"

UCLASS()
class OBJECTIF_GOAP_API AAgent : public ACharacter
{
	GENERATED_BODY()

public:
	AAgent();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<EWorldStateEnum> worldState;
	UPROPERTY(EditAnywhere)
	TArray<EGoalEnum> goals;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UAgentAction>> allActions;
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<UAgentAction>> currentActions; 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
