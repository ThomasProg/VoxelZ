// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FunctionLibraries/Structures.h"
#include "WorldStructuresSave.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UWorldStructuresSave : public USaveGame
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FIntVector> StructsSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FS_BlockChunkArray> StructsFields;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGeneratedStructs_Array> Options;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FS_BlockChunkArrayLocated> longStructFields;
};
