// Fill out your copyright notice in the Description page of Project Settings.

#include "Simplex.h"

#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
//#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"


#pragma region "1D"

	#pragma region "Peaks"

float USimplex::GetMultiplePeaks1D(float location, float distance)
{
	return floor((location + distance / 2) / distance)*distance;
}

float USimplex::GetMultiplePeaksInCorner1D(float location, float distance)
{
	return floor(location / distance)*distance;
}

	#pragma endregion "Peaks"

#pragma endregion "1D"



#pragma region "2D"

	#pragma region "Simplex"

float USimplex::Simplex2D(FVector2D location, FVector2D peakLocation, float mountainLength, float heightPerBlock, float topRayonSurface)
{
	float distance = (peakLocation - location).Size();

	if (distance > mountainLength)
	{
		return 0.0;
	}
	else
	{
		if (distance < topRayonSurface)
		{
			distance = topRayonSurface;
		}
		//return ((peakLocation - FVector2D(peakLocation.X/*+mountainLength*/, peakLocation.Y/*+ mountainLength*/)).Size()*(-1) + distance)* heightPerBlock;

		return (mountainLength - distance)*heightPerBlock;
	}

}

float USimplex::Simplex2D_cos(FVector2D location, FVector2D peakLocation, float mountainLength, float heightPerBlock, float topRayonSurface)
{
	float distance = (peakLocation - location).Size();

	if (distance > PI/mountainLength)
	{
		return 0.0;
	}
	else
	{
		if (distance < topRayonSurface)
		{
			distance = 0;
		}
		//return ((peakLocation - FVector2D(peakLocation.X/*+mountainLength*/, peakLocation.Y/*+ mountainLength*/)).Size()*(-1) + distance)* heightPerBlock;

		return cos(distance*mountainLength)*heightPerBlock + heightPerBlock;
	}

}

//float USimplex::Simplex2D_expo(FVector2D location, FVector2D peakLocation, float mountainLength, float heightPerBlock, float topRayonSurface)
//{
//	float distance = (peakLocation - location).Size();
//
//	if (distance > PI / mountainLength)
//	{
//		return 0.0;
//	}
//	else
//	{
//		if (distance < topRayonSurface)
//		{
//			distance = 0;
//		}
//		//return ((peakLocation - FVector2D(peakLocation.X/*+mountainLength*/, peakLocation.Y/*+ mountainLength*/)).Size()*(-1) + distance)* heightPerBlock;
//
//		//return cos(distance*mountainLength)*heightPerBlock + heightPerBlock;
//		return FGenericPlatformMath::Exp(-distance ^ 2);
//	}
//
//}


float USimplex::SimplexDonut2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock)
{
	FVector2D d = location - peakLocation;
	float h = (mountainRadius*heightPerBlock) - abs(circleRadius-sqrt(d.X*d.X+d.Y*d.Y))*heightPerBlock;

	if (h < 0.0f)
		return 0.0f;
	else
		return h;
}

float USimplex::SimplexArc2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock, float blockPerDegree, float rotation)
{
	FVector2D d = location - peakLocation;
	float h = (mountainRadius*heightPerBlock) - abs(circleRadius - sqrt(d.X*d.X + d.Y*d.Y))*heightPerBlock;

	float degrees = abs(atan(d.Y / d.X)) + rotation;
	h += blockPerDegree * (degrees > 180 ? 180 - (fmod(degrees,180)) : degrees);

	if (h < 0.0f)
		return 0.0f;
	else
		return h;
}

float USimplex::SimplexArcAttenuation2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock, float blockPerDegree, float rotation, float flatnessHeight, float flatness)
{
	FVector2D d = location - peakLocation;
	float h = (mountainRadius*heightPerBlock) - abs(circleRadius - sqrt(d.X*d.X + d.Y*d.Y))*heightPerBlock;

	float degrees = abs(atan(d.Y / d.X)) + rotation;
	h += blockPerDegree * (degrees > 180 ? 180 - (fmod(degrees, 180)) : degrees);

	if (h < 0.0f)
		return 0.0f;
	else
	{
		if (h < flatnessHeight)
			return h;
		else
			return (h - flatnessHeight)*flatness + flatnessHeight;
	}
}

	#pragma endregion "Simplex"

	#pragma region "Peaks"

FVector2D USimplex::GetMultiplePeaks2D(FVector2D location, FVector2D distance)
{
	return FVector2D(
		floor((location.X+distance.X/2)/distance.X)*distance.X, 
		floor((location.Y+distance.Y/2)/distance.Y)*distance.Y
	);
}

FVector2D USimplex::GetMultiplePeaksInCorner2D(FVector2D location, FVector2D distance)
{
	return FVector2D(
		floor(location.X / distance.X)*distance.X,
		floor(location.Y / distance.Y)*distance.Y
	);
}

	#pragma endregion "Peaks"

	#pragma region "Dilations"

FVector2D USimplex::Rectangle_Dilation2D(FVector2D peakLocation, FVector2D location, FVector2D distance)
{
	return (location - (distance*(location-peakLocation)));
}

FVector2D USimplex::Diagonale_Dilation2D(FVector2D peakLocation, FVector2D location, FVector2D distance)
{
	FVector2D a = distance * (location - peakLocation);
	return (location - FVector2D(a.Y, a.X));
}

	#pragma endregion "Dilations"

	FVector2D USimplex::ErrorTolerance2D(FVector2D a, FVector2D errorTolerance)
{
	//return FVector2D(a.Y < 0.0f ? fmod(a.Y,errorTolerance.X) + errorTolerance.X : fmod(a.Y,errorTolerance.X), a.X < 0.0f ? fmod(a.X,errorTolerance.Y + errorTolerance.Y) : fmod(a.X,errorTolerance.Y))*(-1);
	FVector2D b;
	b.X = fmod(a.Y, errorTolerance.X);
	if (b.X < 0)
		b.X += errorTolerance.X;

	b.Y = fmod(a.X, errorTolerance.Y);
	if (b.Y < 0)
		b.Y += errorTolerance.Y;
	return b;
}

#pragma region "multiSimplex"

	//float USimplex::Simplex2D(FVector2D peakDistance, FVector2D location, FVector2D peakLocation, float mountainLength, float heightPerBlock, float topRayonSurface)
	float USimplex::multiSimplex(TArray<FS_multiSimplex> list)
	{
		float total = 0.0;

		for (FS_multiSimplex i : list)
		{
		FVector2D peakLocation = USimplex::GetMultiplePeaks2D(i.location, i.peakDistance);
		total += USimplex::Simplex2D(i.peakDistance, i.location, i.mountainLength, i.heightPerBlock, i.topRayonSurface);
		}

		return total;
	}


#pragma endregion "multiSimplex"

#pragma region "heightmap"


	void USimplex::zoom(UPARAM(ref) TArray<int32>& arr, UPARAM(ref) int32& size)
	{
		int added = 0;

		for (int y = 0; y < size; y++)
		{


			for (int x = 1; x < size; x++)  // 0 1 0 1 0 1 0 0
			{
				int id = x + y * size + added;

				int newValue = 0;
				switch (FMath::RandRange(0, 2))
				{
				case 0: {newValue = arr[id - 1]; break; }
				case 1: newValue = arr[id];
				}

				if (arr.IsValidIndex(id))
					arr.Insert(newValue, id);
				added++;
			}

			for (int x = 0; x < size + size - 1; x++)  // 0 1 0 1 0 1 0 0     0 0 0
			{                                                        //   0 1 0
				int id = (y + 1)*size + added;

				int newValue = 0;
				if (x % 2 == 0)
				{
					switch (FMath::RandRange(0,2))
					{
					case 0: {newValue = arr[id - size - size + 1]; break; }
					case 1: newValue = arr[id + x / 2];
					}
				}
				else
				{
					switch (FMath::RandRange(0, 4))
					{
					case 0: {newValue = arr[id - size - size]; break; }
					case 1: {newValue = arr[id - size - size + 2]; break; }
					case 2: {newValue = arr[id + x / 2]; break; }
					case 3: newValue = arr[id + x / 2 + 1];
					}
					//newValue = arr[id-size-size];
					//newValue = arr[id-size-size+2];
					//newValue = arr[id+x/2];
					//newValue = arr[id+x/2]+1;
				}

				if (arr.IsValidIndex(id))
					arr.Insert(newValue,id);
				added++;
			}

			//added+=size+size-1;

		}
		size = size + size - 1;
	}

	void USimplex::FillBorders(UPARAM(ref) TArray<int32>& arr, const int32& size)
	{
		for (int i = 0; i < size; i++)    //fill borders
		{
			arr[i] = 0;
			arr[size*size - i] = 0;
			arr[i*size] = 0;
			arr[i*size + size - 1] = 0;

		}
	}

	void USimplex::DrawPointAtCenter(UPARAM(ref) TArray<int32>& arr)
	{
		//arr[(size - 1) / 2 + size * (size - 1) / 2] = 1;
		arr[arr.Num() / 2] = 1;
	}

#pragma endregion "heightmap"

#pragma endregion "2D"



#pragma region "3D"

	#pragma region "Simplex"

	bool USimplex::Simplex3D(FVector location, FVector peakLocation, float radius, FVector maxRadiusOnAxis)	 //sphere
	{
		FVector difference = location - peakLocation;
		float distance = (difference).Size();

		if (distance > radius)
		{
			return false;
		}
		else
		{
			if (abs(difference.X) > maxRadiusOnAxis.X || abs(difference.Y) > maxRadiusOnAxis.Y || abs(difference.Z) > maxRadiusOnAxis.Z)
			{
				return false;
			}
			else
				return true;
		}

	}

	bool USimplex::SimplexDonut3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation)
	{
		location = rotation.RotateVector(location);
		peakLocation = rotation.RotateVector(peakLocation);

		FRotator e = UKismetMathLibrary::FindLookAtRotation(peakLocation, location);

		FVector realSphereLocation = UKismetMathLibrary::GetForwardVector(FRotator(0, e.Yaw, 0)) * circleRadius + peakLocation;

				if ((realSphereLocation - location).Size() < caveRadius)
				{
					if (abs((realSphereLocation - location).X) > caveRadiusOnAxis.X || abs((realSphereLocation - location).Y) > caveRadiusOnAxis.Y || abs((realSphereLocation - location).Z) > caveRadiusOnAxis.Z)
						return false;
					else
						return true;
				}
				else
					return false;

	}

	bool USimplex::SimplexArc3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation, float heightPerBlock)
	{
		location = rotation.RotateVector(location);
		peakLocation = rotation.RotateVector(peakLocation);

		FRotator e = UKismetMathLibrary::FindLookAtRotation(peakLocation, location);

		FVector realSphereLocation = UKismetMathLibrary::GetForwardVector(FRotator(0.0, e.Yaw, 0.0)) * circleRadius + peakLocation;

		if ((realSphereLocation - location).Size() < caveRadius - ((UKismetMathLibrary::GetForwardVector(FRotator(0.0, e.Yaw, 0.0)) * circleRadius + peakLocation) - realSphereLocation).Size()*heightPerBlock)
		{
			if (abs((realSphereLocation - location).X) > caveRadiusOnAxis.X || abs((realSphereLocation - location).Y) > caveRadiusOnAxis.Y || abs((realSphereLocation - location).Z) > caveRadiusOnAxis.Z)
				return false;
			else
				return true;
		}
		else
			return false;
	}

	bool USimplex::SimplexArcAttenuation3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation, float heightPerBlock, float limit)
	{
		location = rotation.RotateVector(location);
		peakLocation = rotation.RotateVector(peakLocation);

		FRotator e = UKismetMathLibrary::FindLookAtRotation(peakLocation, location);

		FVector realSphereLocation = UKismetMathLibrary::GetForwardVector(FRotator(0.0, e.Yaw, 0.0)) * circleRadius + peakLocation;

		float att = ((UKismetMathLibrary::GetForwardVector(FRotator(0.0, 0.0, 0.0)) * circleRadius + peakLocation) - realSphereLocation).Size();

		if (att > limit)
			att = (att - limit)*heightPerBlock;
		else
			att = 0;

		if ((realSphereLocation - location).Size() < caveRadius - att)
		{
			if (abs((realSphereLocation - location).X) > caveRadiusOnAxis.X || abs((realSphereLocation - location).Y) > caveRadiusOnAxis.Y || abs((realSphereLocation - location).Z) > caveRadiusOnAxis.Z)
				return false;
			else
				return true;
		}
		else
			return false;
	}

	#pragma endregion "Simplex"

	#pragma region "Peaks"

FVector USimplex::GetMultiplePeaks3D(FVector location, FVector distance)
{
	return FVector(
		floor((location.X + distance.X / 2) / distance.X)*distance.X,
		floor((location.Y + distance.Y / 2) / distance.Y)*distance.Y,
		floor((location.Z + distance.Z / 2) / distance.Z)*distance.Z
	);
}

FVector USimplex::GetMultiplePeaksInCorner3D(FVector location, FVector distance)
{
	return FVector(
		floor(location.X / distance.X)*distance.X,
		floor(location.Y / distance.Y)*distance.Y,
		floor(location.Z / distance.Z)*distance.Z
	);
}

	#pragma endregion "Peaks"

#pragma endregion "3D"