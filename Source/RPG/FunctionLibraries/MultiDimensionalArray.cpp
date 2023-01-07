// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiDimensionalArray.h"


//UObjectBase UMultiDimensionalArray::Get(const FArray3D Array, const int32 x, const int32 y, const int32 z)
//{
//	return Array.ArrayValues[x + y * Array.ArraySize.X + z * Array.ArraySize.X*Array.ArraySize.Y];
//}
//
//bool UMultiDimensionalArray::IsValid(const FArray3D Array, const int32 x, const int32 y, const int32 z)
//{
//	int32 id = x + y * Array.ArraySize.X + z * Array.ArraySize.X*Array.ArraySize.Y;
//	if (id < 0 || id >= Array.ArrayValues.Num())
//		return false;
//	else
//		return true;
//}


int UMultiDimensionalArray::Get1DFrom3D(FIntVector a, FIntVector Size)
{
	return a.X + a.Y*Size.X + a.Z*Size.X*Size.Y;
}

FIntVector UMultiDimensionalArray::Get3DFrom1D(int32 a, FIntVector Size)
{
	int32 z = a / (Size.X*Size.Y);
	int32 b = a % (Size.X*Size.Y);

	int32 y = b / (Size.X);
	int32 x = a % (Size.X);

	return FIntVector(x,y,z);
}