#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFolderColorizerModule : public IModuleInterface
{
public:
	// IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Apply colors to every existing path under /Game. Called on startup and after settings change. */
	void ApplyAllFolderColors();

	/** Apply a color to a single content-browser path. */
	static void ApplyColorToPath(const FString& Path);

	/** Called by the asset registry when a new folder path is registered. */
	static void OnContentPathAdded(const FString& NewPath);

	/** Re-applies all colors whenever the settings asset is edited. */
	void OnSettingsChanged();

	/** Delegate handle so we can unbind cleanly on shutdown. */
	FDelegateHandle PathAddedHandle;
	FDelegateHandle SettingsChangedHandle;
};