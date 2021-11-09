// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlusPlusGameMode.h"
#include "PlusPlusPawn.h"

APlusPlusGameMode::APlusPlusGameMode()
{
	// set default pawn class to our flying pawn
	DefaultPawnClass = APlusPlusPawn::StaticClass();
}
