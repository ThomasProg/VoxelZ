// Fill out your copyright notice in the Description page of Project Settings.

#include "Moon_Refetential.h"

void AMoon_Refetential::GenerateBlock_OneTime/*_Implementation*/(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)
{
	chunk[index].Objects.SetNumZeroed(1);
	int32& block = chunk[index].Objects[0].blockType;
	//int32& block = originalBlock.Objects[0].blockType;
	const int32& x = worldLocation.X; const int32& y = worldLocation.Y; const int32& z = worldLocation.Z;
	const int32& noise = noiseArray[relativeLocation.X + relativeLocation.Y * chunkLineElements.X];

	block = 0;
	//if (location.Z < 0)
	//	block = 1;

	//if (z <= 30)	 // = niveau de l'eau
	//	block = 2;
	//else
	//	block = 0;
	//if (z <= 30)
	//	block = 14;

	//if (z + ChunkCoordonates.Z*chunkTotalElements <= 0)
	if (noiseArray.Num() > (relativeLocation.X + relativeLocation.Y * chunkLineElements.X))
	{

		if (z < 30 + noise)	//ground
												//if (z + ChunkCoordonates.Z*chunkLineElements.Z < 30 + SimplexNoise2D(x, y));
		{
			block = 14;
		}


		bool isStructured = false;
		int32 newID = GenerateStruct_OneTime(worldLocation, noise, isStructured);
		if (isStructured)
			block = newID;
	}

	if (block == 0)
		chunk[index].Objects.RemoveAt(0);
}