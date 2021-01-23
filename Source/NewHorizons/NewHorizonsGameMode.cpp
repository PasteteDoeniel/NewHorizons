// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewHorizonsGameMode.h"
#include "NewHorizonsHUD.h"
#include "NewHorizonsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANewHorizonsGameMode::ANewHorizonsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Ship"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANewHorizonsHUD::StaticClass();
}