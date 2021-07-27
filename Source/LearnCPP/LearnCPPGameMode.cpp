// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LearnCPPGameMode.h"
#include "LearnCPPHUD.h"
#include "LearnCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALearnCPPGameMode::ALearnCPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ALearnCPPHUD::StaticClass();
}
