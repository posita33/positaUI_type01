// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "positaUI_type01Style.h"

class FpositaUI_type01Commands : public TCommands<FpositaUI_type01Commands>
{
public:

	FpositaUI_type01Commands()
		: TCommands<FpositaUI_type01Commands>(TEXT("positaUI_type01"), NSLOCTEXT("Contexts", "positaUI_type01", "positaUI_type01 Plugin"), NAME_None, FpositaUI_type01Style::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};