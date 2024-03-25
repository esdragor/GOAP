// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumUtils.h"
#include "GameFramework/Character.h"
#include "AIAgent.generated.h"

class UAgentAction;

UCLASS()
class AIGOAP_API AAIAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIAgent();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void NeedToSetupPlan();

public:	


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<EWorldStateEnum> worldState;
	UPROPERTY(EditAnywhere)
	TArray<EWorldStateEnum> goals;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UAgentAction>> allActions;
	UPROPERTY(VisibleAnywhere)
	TArray<TSubclassOf<UAgentAction>> currentActions; 

};
