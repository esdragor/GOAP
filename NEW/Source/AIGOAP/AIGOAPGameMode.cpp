// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIGOAPGameMode.h"
#include "AIGOAPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIGOAPGameMode::AAIGOAPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
