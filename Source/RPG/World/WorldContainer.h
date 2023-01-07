// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionLibraries/Structures.h"
#include "FunctionLibraries/Utilities.h"
#include "Engine.h"
#include "WorldContainer.generated.h"

UCLASS()
class RPG_API AWorldContainer : public AActor
{
	GENERATED_BODY()
	
private:


public:	
	// Sets default values for this actor's properties
	AWorldContainer();

	void GetLifetimeReplicatedProps(class TArray<class FLifetimeProperty, class FDefaultAllocator> &) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		void LoadChunks();
	virtual void LoadChunks_Implementation();

	UFUNCTION(BlueprintCallable)
		void LoadChunksOnceMax();


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chunks", Replicated)
		TArray<FIntVector> chunkCoordonates;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chunks", Replicated)
		TArray<FS_BlockChunkArray> chunkFields;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Structs", Replicated)
		TArray<FIntVector> structSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Structs", Replicated)
		TArray<FS_BlockChunkArray> structFields;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Structs", Replicated)
		TArray<FS_BlockChunkArrayLocated> structFieldsLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Structs", Replicated)
		TArray<FGeneratedStructs_Array> structOptions;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Water", Replicated)
		TArray<FWaterToDo> waterToDo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
		FVector baseLocation;


#pragma region "referential"		   

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chunk properties")
		FText refName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chunk properties")
		FIntVector chunkLineElements;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chunk properties")
		FVector cubeSize;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		int32 CalculateNoise_OneTime(const FIntPoint& location);
	virtual int32 CalculateNoise_OneTime_Implementation(const FIntPoint& location);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		//void GenerateBlock_OneTime(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, const TArray<FblockProperties>& chunk, int32 index);
	virtual void GenerateBlock_OneTime/*_Implementation*/(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		int32 GenerateStruct_OneTime(const FIntVector& location, const int32& noise, bool& isValidStruct);
	virtual int32 GenerateStruct_OneTime_Implementation(const FIntVector& location, const int32& noise, bool& isValidStruct);

	UFUNCTION(BlueprintCallable)
		void GenerateStruct_sub(const FIntVector& location, const int32& noise, const int32 structID, const FVector2D peakDistance, const FVector2D errorTolerance, const int32 noiseAdded, bool& isValidStruct, int32& blockType, FVector2D& peakLocation);
	UFUNCTION(BlueprintCallable)
		void GenerateLargeStruct_sub(const FIntVector& location, const int32& noise, const int32 structID, const FVector2D peakDistance, const FVector2D errorTolerance, const int32 noiseAdded, bool& isValidStruct, int32& blockType, FVector2D& peakLocation);


#pragma endregion "referential"

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		void SpawnVoxel(FVector location, FTransform& transform, FVector& FVoxelSize, FIntVector& FChunkLineElements);
	virtual void SpawnVoxel_Implementation(FVector location, FTransform& transform, FVector& FVoxelSize, FIntVector& FChunkLineElements);

#pragma region "physics"

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//	void LiquidPropagation(FIntVsector chunkLocation, FVector localPos, int32 chunkIndex, bool& currentBlockChange, int32& newBlock);
	//virtual void LiquidPropagation_Implementation(FIntVector chunkLocation, FVector localPos, int32 chunkIndex, bool& currentBlockChange, int32& newBlock);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void LiquidPropagation(FIntVector chunkLocation, FVector worldLoc, FVector relativeLoc, int32 chunkIndex, bool& currentBlockChange, int32& newBlock);
	virtual void LiquidPropagation_Implementation(FIntVector chunkLocation, FVector worldLoc, FVector relativeLoc, int32 chunkIndex, bool& currentBlockChange, int32& newBlock);

#pragma endregion "physics"


#pragma region "utilities"

	UFUNCTION(BlueprintCallable)
	virtual FIntVector ReferentialGetChunkAndRelativeLocation(FVector WorldLocation, FS_FloatAndIntVectors& chunk);

	UFUNCTION(BlueprintCallable)
	virtual FIntVector ReferentialRelativeLocation(FVector WorldLocation);
	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void getBlock(FIntVector chunkLocation, FIntVector relativeLoc, FIntVector worldLoc, bool& isValid,FblockProperties& returnedBlock);
	virtual void getBlock_Implementation(FIntVector chunkLocation, FIntVector relativeLoc, FIntVector worldLoc, bool& isValid, FblockProperties& returnedBlock);

#pragma endregion "utilities"

	bool hasLoadedChunks = false;

};
