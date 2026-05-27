#include "FolderColorizerModule.h"

#include "AssetViewUtils.h"
#include "FolderColorizerSettings.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FolderColorizer"

IMPLEMENT_MODULE(FFolderColorizerModule, FolderColorizer)

/** Returns the last path segment, e.g. "/Game/Blueprints/Player" -> "Player" */
static FString GetLeafName(const FString& Path)
{
	int32 SlashIdx;
	if (Path.FindLastChar(TEXT('/'), SlashIdx))
	{
		return Path.Mid(SlashIdx + 1);
	}
	return Path;
}

void FFolderColorizerModule::StartupModule()
{
	// Bind to settings changes so a re-apply fires whenever the user edits rules.
	UFolderColorizerSettings* Settings = GetMutableDefault<UFolderColorizerSettings>();
	
	SettingsChangedHandle = Settings->OnSettingsChanged.AddRaw(this, &FFolderColorizerModule::OnSettingsChanged);

	// Bind to the asset registry path-added event for auto-coloring new folders.
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	PathAddedHandle = AssetRegistryModule.Get().OnPathAdded().AddRaw(this, &FFolderColorizerModule::OnContentPathAdded);

	// Color all folders that already exist in the project.
	ApplyAllFolderColors();
}

void FFolderColorizerModule::ShutdownModule()
{
	// Remove the settings-change binding.
	UFolderColorizerSettings* Settings = GetMutableDefault<UFolderColorizerSettings>();
	
	Settings->OnSettingsChanged.Remove(SettingsChangedHandle);

	// Remove the asset-registry binding.
	if (FModuleManager::Get().IsModuleLoaded(TEXT("AssetRegistry")))
	{
		const FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		AssetRegistryModule.Get().OnPathAdded().Remove(PathAddedHandle);
	}
}

void FFolderColorizerModule::ApplyAllFolderColors()
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	TArray<FString> Paths;
	AssetRegistryModule.Get().GetAllCachedPaths(Paths);

	for (const FString& Path : Paths)
	{
		ApplyColorToPath(Path);
	}
}

void FFolderColorizerModule::ApplyColorToPath(const FString& Path)
{
	const UFolderColorizerSettings* Settings = GetDefault<UFolderColorizerSettings>();
	const FString LeafName = GetLeafName(Path);
	const TOptional<FLinearColor> Color = Settings->GetColorForFolder(LeafName);
	
	if (!Color.IsSet())
	{
		return;
	}

	AssetViewUtils::SetPathColor(Path, Color);
}

void FFolderColorizerModule::OnContentPathAdded(const FString& NewPath)
{
	if (const UFolderColorizerSettings* Settings = GetDefault<UFolderColorizerSettings>(); Settings->bAutoColorNewFolders)
	{
		ApplyColorToPath(NewPath);
	}
}

void FFolderColorizerModule::OnSettingsChanged()
{
	ApplyAllFolderColors();
}

#undef LOCTEXT_NAMESPACE