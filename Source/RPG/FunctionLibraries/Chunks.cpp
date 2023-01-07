// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunks.h"

FS_FloatAndIntVectors UChunks::GetChunk(FVector ChunkSize, FVector CubeSize, FVector Location)
{
	FS_FloatAndIntVectors a;
	FVector x = ChunkSize * CubeSize;
	a = UUtilities::FVector_Floor(Location / x);
	a.a *= x;
	return a;
}

FIntVector UChunks::GetRelativeLocation(FVector ChunkSize, FVector CubeSize, FVector WorldLocation)
{
	return FIntVector((WorldLocation - UChunks::GetChunk(ChunkSize, CubeSize, WorldLocation).a)/ CubeSize);
}

FIntVector UChunks::GetChunkAndRelativeLocation(FVector ChunkSize, FVector CubeSize, FVector WorldLocation, FS_FloatAndIntVectors& chunk)
{
	chunk = UChunks::GetChunk(ChunkSize, CubeSize, WorldLocation);
	return UUtilities::FVector_Floor((WorldLocation - chunk.a) / CubeSize).b;
}

FIntVector UChunks::GetChunkLocalCubePosition(FVector ChunkSize, FVector CubeSize, FVector Location)
{
	FIntVector w = FIntVector(Location / CubeSize);
	w = FIntVector(FMath::Fmod(w.X, ChunkSize.X), FMath::Fmod(w.Y, ChunkSize.Y), FMath::Fmod(w.Z, ChunkSize.Z));
	if (w.X < ChunkSize.X)
		w.X += ChunkSize.X;
	if (w.Y < ChunkSize.Y)
		w.Y += ChunkSize.Y;
	if (w.Z < ChunkSize.Z)
		w.Z += ChunkSize.Z;
	return w;
}

float UChunks::GetGlobalCoordonates1D(float LocalCoordonates, float ChunkCoordonates, float ChunkLineElements)
{
	return LocalCoordonates + ChunkCoordonates * ChunkLineElements;
}

FVector UChunks::GetGlobalCoordonates3D(FVector LocalCoordonates, FVector ChunkCoordonates, FVector ChunkLineElements)
{
	return LocalCoordonates + ChunkCoordonates * ChunkLineElements;
}

FS_FindChunk UChunks::Search(TArray<FIntVector> TargetArray, FIntVector ToFind)
{
	if (TargetArray.Num() > 0)
	{
		if (TargetArray[0] == ToFind)
		{
			FS_FindChunk result;
			result.Found = true;
			result.index = 0;
			return result;
		}
		//if (TargetArray.Num() > 1)
		//{
		//	if (TargetArray[1] == ToFind)
		//	{
		//		FS_FindChunk result;
		//		result.Found = true;
		//		result.index = 1;
		//		return result;
		//	}
		//}
		int min = 0;
		int max = TargetArray.Num() - 1;
		int actu = max / 2;
		
		do
		{
			if (TargetArray[actu] == ToFind)
			{
				FS_FindChunk result;
				result.Found = true;
				result.index = actu;
				return result;
			}
			else
			{
				if (UUtilities::FIntVector_greaterThan_FIntVector(TargetArray[actu], ToFind))
				{
					max = actu;
					actu = min + ((max - min) / 2);
					if ((max - min) % 2 == 1)
						actu += 1;
				}
				else
				{
					min = actu;
					actu = min + ((max - min) / 2);
					if ((max - min) % 2 == 1)
						actu += 1;
				}
			}
		} while (actu != min && actu != max);
		FS_FindChunk result;
		result.Found = false;
		if (UUtilities::FIntVector_greaterThan_FIntVector(ToFind,TargetArray[actu]))
			result.index = actu+1;
		else
		{
			if (actu > 0)
			{
				if (UUtilities::FIntVector_greaterThan_FIntVector(ToFind, TargetArray[actu - 1]))
					result.index = actu;
				else
					result.index = actu-1;
			}
			else 
				result.index = actu;
		}
		return result;
	}
	else
	{
		FS_FindChunk result;
		result.Found = false;
		result.index = 0;
		return result;
	}
}

FS_FloatAndIntVectors UChunks::CoordonatesToCases(FVector Coordonates, FVector CaseSize)
{
	FVector r = Coordonates / CaseSize;
	FS_FloatAndIntVectors v;
	v.b.X = floor(r.X);
	v.b.Y = floor(r.Y);
	v.b.Z = floor(r.Z);
	v.a = CaseSize * FVector(v.b.X, v.b.Y, v.b.Z);
	return v;
}

