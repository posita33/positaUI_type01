// Copyright Epic Games, Inc. All Rights Reserved.

#include "positaUI_type01.h"
#include "positaUI_type01Style.h"
#include "positaUI_type01Commands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "ToolMenus.h"

static const FName positaUI_type01TabName("positaUI_type01");

#define LOCTEXT_NAMESPACE "FpositaUI_type01Module"

void FpositaUI_type01Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FpositaUI_type01Style::Initialize();
	FpositaUI_type01Style::ReloadTextures();

	FpositaUI_type01Commands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FpositaUI_type01Commands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FpositaUI_type01Module::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FpositaUI_type01Module::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(positaUI_type01TabName, FOnSpawnTab::CreateRaw(this, &FpositaUI_type01Module::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FpositaUI_type01TabTitle", "positaUI_type01"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FpositaUI_type01Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FpositaUI_type01Style::Shutdown();

	FpositaUI_type01Commands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(positaUI_type01TabName);
}

TSharedRef<SDockTab> FpositaUI_type01Module::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	PropertyNumText = FText::AsNumber(PropertyNumValue);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(10.0f, 3.0f, 10.0f, 3.0f)
					.AutoWidth()
					[
						SNew(SButton)
						.Text(LOCTEXT("Button", "Button"))
						.OnClicked_Raw(this, &FpositaUI_type01Module::HandleButton)
					]
					+ SHorizontalBox::Slot()
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text_Raw(this, &FpositaUI_type01Module::GetPropertyNumText)
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(10.0f, 3.0f, 10.0f, 3.0f)
					.VAlign(VAlign_Center)
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("PropertyNum", "PropertyNum"))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SNumericEntryBox<int32>)
						.IsEnabled(true)
						.AllowSpin(true)
						.MinSliderValue(1)
						.MaxSliderValue(10000)
						.MinDesiredValueWidth(75)
						.Value_Raw(this, &FpositaUI_type01Module::GetPropertyNumValue)
						.OnValueChanged_Raw(this, &FpositaUI_type01Module::OnPropertyNumValueChanged)
					]
				]
			]
		];
}

void FpositaUI_type01Module::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(positaUI_type01TabName);
}

void FpositaUI_type01Module::OnPropertyNumValueChanged(int32 InValue)
{
	PropertyNumValue = InValue;
}

FReply FpositaUI_type01Module::HandleButton()
{
	// PropertyNumValue‚ðFText‚É•ÏŠ·‚µ‚ÄPropertyNumText‚ÉÝ’è
	PropertyNumText = FText::AsNumber(PropertyNumValue);

	return FReply::Handled();
}

void FpositaUI_type01Module::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FpositaUI_type01Commands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FpositaUI_type01Commands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FpositaUI_type01Module, positaUI_type01)