// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumUtils.generated.h"

UENUM(BlueprintType)
enum class EWorldStateEnum
{
	HaveWood,
	CloseToForest,
	CloseToBase,
	HaveWoodAtBase,
	CloseToEnemy,
	SeeEnemy,
	SeeWoodInDeadBody,
	
};
UENUM(BlueprintType)
enum class EGoalEnum
{
	DropWood,
	Patrol,
	SteelWood,
	Attack,
};
