#include "FolderColorizerSettings.h"

#include "Misc/WildcardString.h"

UFolderColorizerSettings::UFolderColorizerSettings()
{
	// ---------------------------------------------------------------
	// Default rule set — covers the most common Unreal project layouts.
	// Users can add, remove, or reorder these in Project Settings.
	// ---------------------------------------------------------------
	ColorRules = {
		{ TEXT("Blueprints"),   		FLinearColor(0.086f, 0.388f, 0.922f) },  
		{ TEXT("Blueprint"),    		FLinearColor(0.086f, 0.388f, 0.922f) },
		{ TEXT("Materials"),    		FLinearColor(0.761f, 0.255f, 0.047f) },
		{ TEXT("Material"),     		FLinearColor(0.761f, 0.255f, 0.047f) },
		{ TEXT("Textures"),     		FLinearColor(0.576f, 0.200f, 0.918f) },
		{ TEXT("Texture"),      		FLinearColor(0.576f, 0.200f, 0.918f) },
		{ TEXT("Meshes"),       		FLinearColor(0.082f, 0.502f, 0.239f) },
		{ TEXT("Mesh"),         		FLinearColor(0.082f, 0.502f, 0.239f) },
		{ TEXT("StaticMeshes"), 		FLinearColor(0.082f, 0.502f, 0.239f) },
		{ TEXT("SkeletalMeshes"),	FLinearColor(0.114f, 0.624f, 0.424f) },

		// Animation
		{ TEXT("Animations"),   		FLinearColor(0.055f, 0.478f, 0.565f) },
		{ TEXT("Animation"),    		FLinearColor(0.055f, 0.478f, 0.565f) },
		{ TEXT("Rigs"),         		FLinearColor(0.055f, 0.478f, 0.565f) },
		
		// Audio		
		{ TEXT("Audio"),        		FLinearColor(0.706f, 0.322f, 0.035f) }, 
		{ TEXT("Sounds"),       		FLinearColor(0.706f, 0.322f, 0.035f) },
		{ TEXT("Sound"),        		FLinearColor(0.706f, 0.322f, 0.035f) },
		{ TEXT("Music"),        		FLinearColor(0.706f, 0.322f, 0.035f) },
		
		// UI
		{ TEXT("UI"),           		FLinearColor(0.745f, 0.094f, 0.353f) },  
		{ TEXT("Widgets"),      		FLinearColor(0.745f, 0.094f, 0.353f) },
		{ TEXT("HUD"),          		FLinearColor(0.745f, 0.094f, 0.353f) },
		{ TEXT("UMG"),          		FLinearColor(0.745f, 0.094f, 0.353f) },
		
		// VFX		
		{ TEXT("VFX"),          		FLinearColor(0.863f, 0.149f, 0.149f) }, 
		{ TEXT("Particles"),    		FLinearColor(0.863f, 0.149f, 0.149f) },
		{ TEXT("Niagara"),      		FLinearColor(0.863f, 0.149f, 0.149f) },
		{ TEXT("Effects"),      		FLinearColor(0.863f, 0.149f, 0.149f) },
		
		// Maps / Levels		
		{ TEXT("Maps"),         		FLinearColor(0.380f, 0.282f, 0.173f) },
		{ TEXT("Levels"),       		FLinearColor(0.380f, 0.282f, 0.173f) },
		{ TEXT("Environments"), 		FLinearColor(0.380f, 0.282f, 0.173f) },
		
		// Data		
		{ TEXT("Data"),         		FLinearColor(0.341f, 0.341f, 0.341f) },
		{ TEXT("DataTables"),   		FLinearColor(0.341f, 0.341f, 0.341f) },
		{ TEXT("Config"),       		FLinearColor(0.341f, 0.341f, 0.341f) },
		
		// Characters / AI		
		{ TEXT("Characters"),   		FLinearColor(0.220f, 0.149f, 0.600f) },
		{ TEXT("AI"),           		FLinearColor(0.220f, 0.149f, 0.600f) },
		{ TEXT("BehaviorTrees"),		FLinearColor(0.220f, 0.149f, 0.600f) },
		
		// Post-process / Rendering
		{ TEXT("PostProcess"),  		FLinearColor(0.055f, 0.314f, 0.478f) },
		{ TEXT("Rendering"),    		FLinearColor(0.055f, 0.314f, 0.478f) },
		{ TEXT("Shaders"),      		FLinearColor(0.055f, 0.314f, 0.478f) },
	};
}

TOptional<FLinearColor> UFolderColorizerSettings::GetColorForFolder(const FString& FolderLeafName) const
{
	for (const FFolderColorRule& Rule : ColorRules)
	{
		if (FolderLeafName.MatchesWildcard(Rule.FolderName))
		{
			return Rule.Color;
		}
	}

	return {};
}