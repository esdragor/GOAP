#pragma once

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


	//GOAL
	DropWood,
	Patrol,
	SteelWood,
	Attack,
};
