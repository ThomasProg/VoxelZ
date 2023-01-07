// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

//#include "Engine.h"
//#include "Saves/ChunkSave.h"
//#include "Kismet/GameplayStatics.h"
#include "FunctionLibraries/Structures.h"

#include "ChunkSave.generated.h"

/**
 * 
 */



UCLASS()
class RPG_API UChunkSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntVector> ChunksCoordonates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FS_BlockChunkArray> ChunksFields;
	
};
