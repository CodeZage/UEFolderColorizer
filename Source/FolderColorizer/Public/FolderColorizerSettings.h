#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FolderColorizerSettings.generated.h"

/**
 * A single folder-name-to-color mapping rule.
 * The FolderName is matched case-insensitively against the last segment of any content path.
 */
USTRUCT(BlueprintType)
struct FFolderColorRule
{
	GENERATED_BODY()

	/** Folder name to match, e.g. "Blueprints". Case-insensitive. Supports * wildcards. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rule")
	FString FolderName;

	/** Color to apply to matching folders. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rule")
	FLinearColor Color = FLinearColor::White;

	FFolderColorRule() {}
	FFolderColorRule(const FString& InName, const FLinearColor& InColor) : FolderName(InName), Color(InColor) {}
};


/**
 * Project-level settings for FolderColorizer.
 * Accessible via Edit > Project Settings > Plugins > Folder Colorizer.
 */
UCLASS(BlueprintType)
class FOLDERCOLORIZER_API UFolderColorizerSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	/** When true, the plugin automatically re-applies colors whenever a new folder is created. */
	UPROPERTY(EditAnywhere, Category = "General")
	bool bAutoColorNewFolders = true;

	/**
	 * List of rules applied in order. The first matching rule wins.
	 * Folder names are matched case-insensitively against the last path segment.
	 */
	UPROPERTY(EditAnywhere, Category = "Rules", meta = (TitleProperty = "FolderName"))
	TArray<FFolderColorRule> ColorRules;

	/** Returns the color for a given folder leaf name, or TOptional empty if no rule matches. */
	TOptional<FLinearColor> GetColorForFolder(const FString& FolderLeafName) const;
};