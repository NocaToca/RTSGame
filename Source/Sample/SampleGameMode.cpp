// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SampleGameMode.h"
#include "SamplePlayerController.h"
#include "SampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASampleGameMode::ASampleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASamplePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}