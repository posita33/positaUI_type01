// Copyright Epic Games, Inc. All Rights Reserved.

#include "positaUI_type01Commands.h"

#define LOCTEXT_NAMESPACE "FpositaUI_type01Module"

void FpositaUI_type01Commands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "positaUI_type01", "Bring up positaUI_type01 window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
