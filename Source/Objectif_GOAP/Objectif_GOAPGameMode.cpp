// Copyright Epic Games, Inc. All Rights Reserved.

#include "Objectif_GOAPGameMode.h"
#include "Objectif_GOAPPlayerController.h"
#include "Objectif_GOAPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AObjectif_GOAPGameMode::AObjectif_GOAPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AObjectif_GOAPPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}