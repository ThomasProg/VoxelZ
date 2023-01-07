// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldContainer.h"

#include "FunctionLibraries/Simplex.h"
#include "FunctionLibraries/Utilities.h"
#include "FunctionLibraries/Chunks.h"
#include "FunctionLibraries/MultiDimensionalArray.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "FunctionLibraries/MultiDimensionalArray.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include "UnrealNetwork.h"


// Sets default values
AWorldContainer::AWorldContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	chunkLineElements = FIntVector(15, 15, 15);
	cubeSize = FVector(100.0, 100.0, 100.0);
}

void AWorldContainer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWorldContainer,chunkCoordonates);
	DOREPLIFETIME(AWorldContainer,chunkFields);

	DOREPLIFETIME(AWorldContainer,structSize);
	DOREPLIFETIME(AWorldContainer,structFields);
	DOREPLIFETIME(AWorldContainer,structOptions);

	DOREPLIFETIME(AWorldContainer,waterToDo);
}

// Called when the game starts or when spawned
void AWorldContainer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldContainer::LoadChunks_Implementation()
{

}

void AWorldContainer::LoadChunksOnceMax()
{
	if (!hasLoadedChunks)
	{
		LoadChunks();
		hasLoadedChunks = true;
	}
}


#pragma region "referential"

	int32 AWorldContainer::CalculateNoise_OneTime_Implementation(const FIntPoint& location)
	{
		return 0;
	}

	int32 AWorldContainer::GenerateStruct_OneTime_Implementation(const FIntVector& location, const int32& noise, bool& isValidStruct)
	{
		return 0;
	}

	void AWorldContainer::GenerateBlock_OneTime/*_Implementation*/(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)
	{

	}

	//void AWorldContainer::GenerateStruct_OneTime_sub(const FIntVector& location, const int32& noise, const int32& structID, const FIntVector)
	//{
	//
	//}

#pragma endregion "referential"

void AWorldContainer::SpawnVoxel_Implementation(FVector location, FTransform& transform, FVector& FVoxelSize, FIntVector& FChunkLineElements)
{
	transform = FTransform(GetActorRotation(),FVector(1.0,1.0,1.0), location);
	FVoxelSize = cubeSize;
	FChunkLineElements = chunkLineElements;
}

void AWorldContainer::GenerateStruct_sub(const FIntVector& location, const int32& noise, const int32 structID, const FVector2D peakDistance, const FVector2D errorTolerance, const int32 noiseAdded, bool& isValidStruct, int32& blockType, FVector2D& peakLocation)
{
	if ((structSize.IsValidIndex(structID)) && (structOptions.IsValidIndex(structID)) && (structFields.IsValidIndex(structID)))
	{
		peakLocation = USimplex::GetMultiplePeaksInCorner2D(FVector2D(location.X, location.Y), peakDistance);
	
		FVector2D erroredLocation = FVector2D(location.X, location.Y) + USimplex::ErrorTolerance2D(peakLocation, errorTolerance)*(-1);

		FVector2D idFloat = UUtilities::FVector2DRange(peakLocation, erroredLocation);
		FIntPoint id = FIntPoint(floor(idFloat.X), floor(idFloat.Y));



		if ((id.X < structSize[structID].X) && (id.Y < structSize[structID].Y) && (id.X >= 0) && (id.Y >= 0))  // isInArray	 for X, Y axis
		{
			if (erroredLocation.X >= peakLocation.X && erroredLocation.Y >= peakLocation.Y)
			{
				int32 index = UMultiDimensionalArray::Get1DFrom3D(FIntVector(id.X,id.Y,0), structSize[structID]);

				if (structOptions[structID].structs.IsValidIndex(index))
				{
					int32 totalNoise = noiseAdded;

					FGeneratedStructs& structure = structOptions[structID].structs[index];

					if (structure.isRelative == VE_relativeToAnotherNoise)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Another : %d"), int(totalNoise)));
						totalNoise += CalculateNoise_OneTime(structure.AnotherLocation);
					}

					if (structure.isRelative == VE_relativeToNoise)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Relative : %d"), int(totalNoise)));
						totalNoise += noise;
					}

					if (location.Z >= totalNoise && location.Z <= totalNoise + structSize[structID].Z)		//isValid Z axis
					{
						//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("%d"),int(totalNoise)));
						int32 finalID = UMultiDimensionalArray::Get1DFrom3D(FIntVector(id.X, id.Y, floor((location.Z - totalNoise) % (structSize[structID].Z + 1) - 1)), structSize[structID]);
					
						if (structFields[structID].ChunkField.IsValidIndex(finalID))
						{
							if (structFields[structID].ChunkField[finalID].Objects.IsValidIndex(0))
							{
								isValidStruct = true;
								blockType = structFields[structID].ChunkField[finalID].Objects[0].blockType;

								return;
							}
						}
					
					}


				}


			}
		}
	}
}

void AWorldContainer::GenerateLargeStruct_sub(const FIntVector& location, const int32& noise, const int32 structID, const FVector2D peakDistance, const FVector2D errorTolerance, const int32 noiseAdded, bool& isValidStruct, int32& blockType, FVector2D& peakLocation)
{
	if ((structSize.IsValidIndex(structID)) && (structOptions.IsValidIndex(structID)) && (structFields.IsValidIndex(structID)))
	{
		peakLocation = USimplex::GetMultiplePeaksInCorner2D(FVector2D(location.X, location.Y), peakDistance);

		FVector2D erroredLocation = FVector2D(location.X, location.Y) + USimplex::ErrorTolerance2D(peakLocation, errorTolerance)*(-1);

		if (structFieldsLocation.IsValidIndex(0))
		{
			for (int i = 0; i < structFieldsLocation[0].ChunkFieldLocations.Num(); i++)
			{
				if (location == FIntVector(peakLocation.X, peakLocation.Y, location.Z) + structFieldsLocation[0].ChunkFieldLocations[i])
				{
					if (structFieldsLocation[0].ChunkField[i].Objects.IsValidIndex(0))
						blockType = structFieldsLocation[0].ChunkField[i].Objects[0].blockType;
					isValidStruct = true;
				}
			}

		}


	}

	//	FVector2D idFloat = UUtilities::FVector2DRange(peakLocation, erroredLocation);
	//	FIntPoint id = FIntPoint(floor(idFloat.X), floor(idFloat.Y));



	//	if ((id.X < structSize[structID].X) && (id.Y < structSize[structID].Y) && (id.X >= 0) && (id.Y >= 0))  // isInArray	 for X, Y axis
	//	{
	//		if (erroredLocation.X >= peakLocation.X && erroredLocation.Y >= peakLocation.Y)
	//		{
	//			int32 index = UMultiDimensionalArray::Get1DFrom3D(FIntVector(id.X, id.Y, 0), structSize[structID]);

	//			if (structOptions[structID].structs.IsValidIndex(index))
	//			{
	//				int32 totalNoise = noiseAdded;

	//				FGeneratedStructs& structure = structOptions[structID].structs[index];

	//				if (structure.isRelative == VE_relativeToAnotherNoise)
	//				{
	//					//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Another : %d"), int(totalNoise)));
	//					totalNoise += CalculateNoise_OneTime(structure.AnotherLocation);
	//				}

	//				if (structure.isRelative == VE_relativeToNoise)
	//				{
	//					//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Relative : %d"), int(totalNoise)));
	//					totalNoise += noise;
	//				}

	//				if (location.Z >= totalNoise && location.Z <= totalNoise + structSize[structID].Z)		//isValid Z axis
	//				{
	//					//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("%d"),int(totalNoise)));
	//					int32 finalID = UMultiDimensionalArray::Get1DFrom3D(FIntVector(id.X, id.Y, floor((location.Z - totalNoise) % (structSize[structID].Z + 1) - 1)), structSize[structID]);

	//					if (structFields[structID].ChunkField.IsValidIndex(finalID))
	//					{
	//						if (structFields[structID].ChunkField[finalID].Objects.IsValidIndex(0))
	//						{
	//							isValidStruct = true;
	//							blockType = structFields[structID].ChunkField[finalID].Objects[0].blockType;

	//							return;
	//						}
	//					}

	//				}


	//			}


	//		}
	//	}
	//}
}

//void AWorldContainer::LiquidPropagation_Implementation(FIntVector chunkLocation, FVector localPos, int32 chunkIndex, bool& currentBlockChange, int32& newBlock)
//{																							   GenerateBlock_OneTime
//	return;
//}

void AWorldContainer::LiquidPropagation_Implementation(FIntVector chunkLocation, FVector worldLoc, FVector relativeLoc, int32 chunkIndex, bool& currentBlockChange, int32& newBlock)
   {
	return;
}								   

FIntVector AWorldContainer::ReferentialGetChunkAndRelativeLocation(FVector WorldLocation, FS_FloatAndIntVectors& chunk)
{
	return UChunks::GetChunkAndRelativeLocation(FVector(chunkLineElements), cubeSize, WorldLocation, chunk);
}

void AWorldContainer::getBlock_Implementation(FIntVector chunkLocation, FIntVector relativeLoc, FIntVector worldLoc, bool& isValid, FblockProperties& returnedBlock)		  //ToFinish
{
	isValid = false;

	FS_FindChunk chunk = UChunks::Search(chunkCoordonates, chunkLocation);
	if (chunk.Found)
	{
		if (chunkFields.IsValidIndex(chunk.index))
		{
			returnedBlock = chunkFields[chunk.index].ChunkField[UMultiDimensionalArray::Get1DFrom3D(relativeLoc, chunkLineElements)];
			isValid = true;
		}

	}
	else
	{
		TArray<int32> noise; noise.Add(CalculateNoise_OneTime_Implementation(FIntPoint(worldLoc.X,worldLoc.Y)));

		TArray<FblockProperties> a; 
		a.SetNumZeroed(1);

		GenerateBlock_OneTime(FIntVector(0.0,0.0,0.0), worldLoc, noise, a, 0);

		returnedBlock = a[0];
	}
}

FIntVector AWorldContainer::ReferentialRelativeLocation(FVector WorldLocation)
{
	return FIntVector(FGenericPlatformMath::RoundToFloat(WorldLocation.X/cubeSize.X), FGenericPlatformMath::RoundToFloat(WorldLocation.Y / cubeSize.Y), FGenericPlatformMath::RoundToFloat(WorldLocation.Z / cubeSize.Z));

 }