// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Public/RuntimeMeshComponent.h"
#include "FunctionLibraries/Structures.h"
#include "World/WorldContainer.h"
#include "VoxelActor.generated.h"

USTRUCT(BlueprintType)
struct FMeshSection
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray <FVector> Vertices;
	UPROPERTY(BlueprintReadWrite)
	TArray <int32> Triangles;
	UPROPERTY(BlueprintReadWrite)
	TArray <FVector> Normals;
	UPROPERTY(BlueprintReadWrite)
	TArray<FVector2D> UVs;
	UPROPERTY(BlueprintReadWrite)
	TArray<FRuntimeMeshTangent> Tangents;
	UPROPERTY(BlueprintReadWrite)
	TArray<FLinearColor> VertexColors;

	UPROPERTY(BlueprintReadWrite)
	int32 elementID = 0;

	//Added for web etc
	UPROPERTY(BlueprintReadWrite)
	int32 meshIndex;
	UPROPERTY(BlueprintReadWrite)
	int32 faceIndex;
};

USTRUCT(BlueprintType)
struct FArr
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray <int32> Arr;
};

UCLASS()
class RPG_API AVoxelActor : public AActor
{
	GENERATED_BODY()

public :

	TArray<FArr> NewChunksElements;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class AVoxelActor> MyVoxelActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <UMaterialInterface *> Materials;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 randomSeed = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	//	int32 voxelSize = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FVector FvoxelSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FVector FvoxelSizeHalf;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	//	int32 chunkLineElements = 10;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	int32 chunkZElements = 80;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FIntVector chunkLineElements = FIntVector(10, 10, 10);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	//	int32 chunkXIndex = 0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	//	int32 chunkYIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FIntVector ChunkCoordonates;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float xMult = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float yMult = 1;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float zMult = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float weight = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float freq = 1;

	UPROPERTY()
		int32 chunkTotalElements;

	UPROPERTY()
		int32 chunkLineElementsP2; // power 2

	UPROPERTY()
		int32 voxelSizeHalf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	//TArray <int32> chunkFields;
	//	TArray<FVector4> chunkFields;		   
		TArray<FblockProperties> chunkFields;

	//virtual TArray<FblockProperties> fields;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AVoxelActor* localVoxelActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <UStaticMeshComponent*> Components;

	//UPROPERTY()
	//	UProceduralMeshComponent* proceduralComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//URuntimeMeshComponent* runTimeComponent;
		TArray<URuntimeMeshComponent*> runTimeComponents;

	void buildRuntimeMesh(TArray<FMeshSection>& meshSections);
	URuntimeMeshComponent* SelectMeshRunTime(int32 i);
	USceneComponent* SceneComponent;

	UFUNCTION(BlueprintCallable)
		TArray<int32> calculateNoise();
	//virtual TArray<int32> calculateNoise_Implementation();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		int32 calculateNoise_OneTime(FIntPoint location);
	virtual int32 calculateNoise_OneTime_Implementation(FIntPoint location);

	UFUNCTION(BlueprintNativeEvent)
		void Load(TArray<FblockProperties>& arr, FIntVector ChunkCoordonates2);
	virtual void Load_Implementation(TArray<FblockProperties>& arr, FIntVector ChunkCoordonates2);

	UFUNCTION(BlueprintNativeEvent)
		void Compon(URuntimeMeshComponent* compo, int32 SectionIndex, FMeshSection Section, bool bCreateCollision, EUpdateFrequency UpdateFrequency);
	virtual void Compon_Implementation(URuntimeMeshComponent* compo, int32 SectionIndex, FMeshSection Section, bool bCreateCollision, EUpdateFrequency UpdateFrequency);

	  	UFUNCTION(BlueprintNativeEvent)
		void CustomMeshes(FVector Location, FMeshSection& MeshSection, int32 meshIndex);
	virtual void CustomMeshes_Implementation(FVector Location, FMeshSection& MeshSection, int32 meshIndex);

	UFUNCTION(BlueprintNativeEvent)
		int32 GenerateBlocks(int32 x, int32 y, int32 z,  int32 id);
	virtual int32 GenerateBlocks_Implementation(int32 x, int32 y, int32 z, int32 id);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
		int32 GenerateStructs(FIntVector location, bool& isStruct, int32 noise);
	virtual int32 GenerateStructs_Implementation(FIntVector location, bool& isStruct, int32 noise);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//	int32 GenerateStructs2(FIntVector location, bool& isStruct, int32 noise);

	UFUNCTION(BlueprintNativeEvent)
		void UpdateMeshBP();
	virtual void UpdateMeshBP_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	virtual void setVoxel(FVector localPos, int32 value);

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	virtual void setBlock(FIntVector localPos, int32 value, FObjectProperties& replacedValue, int32 objectIndex = 0);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform & Transform) override;

	//virtual void SaveChunk();
	//virtual void LoadChunk();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	virtual void GenerateChunk(TArray<int32>& arr);

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	virtual void GenerateBlock2(FIntVector relativeLocation, FIntVector worldLocation, TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index);

	UFUNCTION(BlueprintCallable, Category = "Voxel")
		virtual void GenerateBlockByBP(FIntVector worldLocation, int32 noise, FblockProperties& returnedBlock);

	UFUNCTION(BlueprintCallable, Category = "Voxel")
		virtual void GenerateChunk2();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	virtual void UpdateMesh();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
		virtual int32 getBlock(FblockProperties a);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Referential", Meta = (ExposeOnSpawn = true))
		AWorldContainer* referential;

	//UFUNCTION(BlueprintCallable, Category = "Voxel")
	//	virtual void UpdateMeshTextures();

	//TArray<FMeshSection> meshSections;
	//meshSections.SetNum(Materials.Num());

	//bool bInitialized = false;

	// Sets default values for this actor's properties
	AVoxelActor();
	

	//bool IsNameStableForNetworking() const override { return true; };

	//bool IsSupportedForNetworking() const override
	//{
	//	return true;
	//}
};
