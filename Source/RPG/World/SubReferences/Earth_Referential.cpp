// Fill out your copyright notice in the Description page of Project Settings.

#include "Earth_Referential.h"


//int32 AEarth_Referential::CalculateNoise_OneTime_Implementation(const FIntPoint& location)
//{
//
//}


void AEarth_Referential::GenerateBlock_OneTime/*_Implementation*/(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)
{
	chunk[index].Objects.SetNumZeroed(1);
	int32& block = chunk[index].Objects[0].blockType;
	//int32& block = originalBlock.Objects[0].blockType;
	const int32& x = worldLocation.X; const int32& y = worldLocation.Y; const int32& z = worldLocation.Z;
	const int32& noise = noiseArray[relativeLocation.X + relativeLocation.Y * chunkLineElements.X];

	block = 0;
	//if (location.Z < 0)
	//	block = 1;

	if (z <= 30)	 // = niveau de l'eau
		block = 2;
	else
		block = 0;

	//if (z + ChunkCoordonates.Z*chunkTotalElements <= 0)
	if (noiseArray.Num() > (relativeLocation.X + relativeLocation.Y * chunkLineElements.X))
	{

		if (z < 30 + noise && z > 27 + noise)	//stone
												//if (z + ChunkCoordonates.Z*chunkLineElements.Z < 30 + SimplexNoise2D(x, y));
		{
			block = 1;

		}
		else
		{
			if (z < 28 + noise)
			{
				int32 randomint11 = FMath::RandRange(0, 99);
				if (randomint11 <= 5)
				{
					if (randomint11 < 3)
						block = 11;
					if (randomint11 >= 3 && randomint11 < 5)
						block = 10;
					if (randomint11 == 5)
						block = 9;
				}
				else
					block = 8;

			}

			else
			{
				if (z == 30 + noise)	 //grass
				{
					//int32 randomint11 = FMath::RandRange(0, 99);
					//if (randomint11 < 5)
					//	chunkFields[index] = 5;
					//else
					if (z < 30)
						block = 1;
					if (z < 25)
						block = 8;
					if (z >= 30)
						block = 4;

					if (x > 15000 / 2)
						block = 13;
					if (x < -15000 / 2)
						block = 14;
				}
				else
				{
					if (z == 31 + noise)	 //grass
					{
						FObjectProperties bigMesh;
						//int32 randomint11 = FMath::RandRange(0, 99);
						//if (randomint11 < 5)
						//	chunkFields[index] = 5;
						//else
						int32 randomint11 = FMath::RandRange(0, 99);
						if (randomint11 < 5)
						{
							//block = 100;
							bigMesh.blockType = 100;
							chunk[index].Objects.Add(bigMesh);
						}
						else
						{
							int32 randomint11 = FMath::RandRange(0, 9999);
							if (randomint11 < 10)
							{
								//block = 101;
								bigMesh.blockType = 100;
								chunk[index].Objects.Add(bigMesh);
							}
						}


					}
				}
			}
		}

		bool isStructured = false;
		int32 newID = GenerateStruct_OneTime(worldLocation, noise, isStructured);
		if (isStructured)
			block = newID;
	}

	if (block == 0)
		chunk[index].Objects.RemoveAt(0);
}

int32 AEarth_Referential::GenerateStruct_OneTime_Implementation(const FIntVector& location, const int32& noise, bool& isValidStruct)
{
	return 0;
}



