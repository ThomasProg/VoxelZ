// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities.h"



bool UUtilities::FIntVector_isEqual(FIntVector a, FIntVector b)
{
	return (a.X == b.X && a.Y == b.Y && a.Z == b.Z);
}

bool UUtilities::FIntVector_isNotEqual(FIntVector a, FIntVector b)
{
	return !FIntVector_isEqual(a, b);
}

bool UUtilities::FIntVector_greaterThan_FIntVector(FIntVector a, FIntVector b)
{
	if (a.X > b.X)
		return true;
	else
	{
		if (a.X < b.X)
			return false;
		else
		{
			if (a.Y > b.Y)
				return true;
			else
			{
				if (a.Y < b.Y)
					return false;
				else
				{
					if (a.Z > b.Z)
						return true;
					else
					{
						if (a.Z < b.Z)
							return false;
						else
							return false;
					}
				}
			}
		}
	}
}

FVector UUtilities::FIntVector_to_FVector(FIntVector a)
{
	return FVector(a.X, a.Y, a.Z);
}

FVector UUtilities::FIntVector_times_FVector(FIntVector a, FVector b)
{
	return FIntVector_to_FVector(a)*b;
}

FIntVector UUtilities::FIntVector_times_FIntVector(FIntVector a, FIntVector b)
{
	return FIntVector(a.X*b.X,a.Y*b.Y,a.Z*b.Z);
}

FIntVector UUtilities::FIntVector_less_FIntVector(FIntVector a, FIntVector b)
{
	return FIntVector(a.X-b.X, a.Y-b.Y, a.Z-b.Z);
}

FIntVector UUtilities::FIntVector_plus_FIntVector(FIntVector a, FIntVector b)
{
	return FIntVector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

FIntVector UUtilities::FIntVector_modulo_FIntVector(FIntVector a, FIntVector b)
{
	return FIntVector(a.X % b.X, a.Y % b.Y, a.Z % b.Z);
}

FS_FloatAndIntVectors UUtilities::FVector_Floor(FVector a)
{
	FS_FloatAndIntVectors b;
	b.a = FVector(floor(a.X), floor(a.Y), floor(a.Z));
	b.b = FIntVector(floor(a.X), floor(a.Y), floor(a.Z));
	return b;
}

float UUtilities::FIfNegativeAdd(float value, float toAdd)
{
	if (value < 0)
		return value + toAdd;
	else
		return value;
}

float UUtilities::FFloatRange(float a, float b)
{
	return abs(b - a);
}

FVector2D UUtilities::FVector2DRange(FVector2D a, FVector2D b)
{
	return FVector2D(abs(b.X - a.X), abs(b.Y - a.Y));
}

FVector UUtilities::FVectorRange(FVector a, FVector b)
{
	return FVector(abs(b.X - a.X), abs(b.Y - a.Y), abs(b.Z - a.Z));
}

int32 UUtilities::Fint32Range(int32 a, int32 b)
{
	return abs(b - a);
}

FIntPoint UUtilities::FIntPointRange(FIntPoint a, FIntPoint b)
{
	return FIntPoint(abs(b.X - a.X), abs(b.Y - a.Y));
}

FIntVector UUtilities::FIntVectorRange(FIntVector a, FIntVector b)
{
	return FIntVector(abs(b.X - a.X), abs(b.Y - a.Y), abs(b.Z - a.Z));
}