// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VoxelActor.h"
#include "World/WorldContainer.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FS_ChunkProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntVector Coordonates;

};

USTRUCT(BlueprintType)
struct FS_EachReferencialChunk_Management
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player properties")
		FIntVector lastPlayerChunk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AVoxelActor*> ChunksRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FIntVector> ChunksLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FS_ChunkProperties> ChunksToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isLimited;

};

UCLASS()
class RPG_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

//#pragma region "VoxelActorsManaging"
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<AVoxelActor*> ChunksRef;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FIntVector> ChunksLocation;
//
////private:
//	TArray<FS_ChunkProperties> ChunksToSpawn;
//
//#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AWorldContainer*> referential;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FS_EachReferencialChunk_Management> chunksManagement;

	UFUNCTION(BlueprintCallable)
		virtual void SpawnVoxel();
	UFUNCTION(BlueprintCallable)
		virtual void DestroyChunks();
	UFUNCTION(BlueprintCallable)
		virtual void NewChunks();

		bool bDoOnce = true;
		int32 SpawningNb = 0;

		int32 switchTick = 0;

public:
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)		   //TO DELETE
	//	FIntVector ChunkLineElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CubeSize;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//FIntVector LastLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntVector range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float frange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector frangeFocus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float frangeMulti;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AVoxelActor> MyVoxelActor;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		AVoxelActor* Start(FS_ChunkProperties location, AWorldContainer* ref);
	virtual AVoxelActor* Start_Implementation(FS_ChunkProperties location, AWorldContainer* ref);

	UFUNCTION(BlueprintNativeEvent)
		void savePlayerLocation();
	virtual void savePlayerLocation_Implementation();

	AVoxelActor* lastVoxel;

	UFUNCTION(BlueprintNativeEvent)
		void NewChunkLocation(AWorldContainer* ref);
	virtual void NewChunkLocation_Implementation(AWorldContainer* ref);

	UFUNCTION(BlueprintCallable)
		virtual void AddReferential(AWorldContainer* ref, bool isLimited);

	UFUNCTION(BlueprintCallable)
		virtual void SetReferentials(TArray<AWorldContainer*> ref);

	UFUNCTION(BlueprintCallable)
		virtual void SortChunksToSpawn();

//#pragma region "referential"
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		TArray<AWorldContainer*> referentials;
//
//#pragma endregion


private:
	AMyPlayerController();
};
