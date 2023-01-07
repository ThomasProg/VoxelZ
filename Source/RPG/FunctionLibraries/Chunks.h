// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Utilities.h"
#include "Chunks.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FS_FindChunk
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Found;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 index;
};

UCLASS()
class RPG_API UChunks : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static FS_FloatAndIntVectors GetChunk(FVector ChunkSize, FVector CubeSize, FVector Location);

	UFUNCTION(BlueprintCallable)
	static FIntVector GetChunkLocalCubePosition(FVector ChunkSize, FVector CubeSize, FVector Location);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetGlobalCoordonates1D(float LocalCoordonates, float ChunkCoordonates, float ChunkLineElements);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetGlobalCoordonates3D(FVector LocalCoordonates, FVector ChunkCoordonates, FVector ChunkLineElements);

	//UFUNCTION(BlueprintCallable)
	//static FS_FindChunk FindChunk(TArray<FIntVector> TargetArray, FIntVector ToFind);
	
	UFUNCTION(BlueprintCallable)
	static FS_FindChunk Search(TArray<FIntVector> TargetArray, FIntVector ToFind);

	UFUNCTION(BlueprintPure,BlueprintCallable,meta=(DisplayName="Convert CoordonatesToCases c++"))
	static FS_FloatAndIntVectors CoordonatesToCases(FVector Coordonates, FVector CaseSize);

	UFUNCTION(BlueprintPure, BlueprintCallable)
		static FIntVector GetRelativeLocation(FVector ChunkSize, FVector CubeSize, FVector WorldLocation);

	UFUNCTION(BlueprintCallable)
		static FIntVector GetChunkAndRelativeLocation(FVector ChunkSize, FVector CubeSize, FVector WorldLocation, FS_FloatAndIntVectors& chunk);
};
