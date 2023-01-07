// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Simplex.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FS_multiSimplex
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D peakDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float mountainLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float heightPerBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float topRayonSurface;
};

UCLASS()
class RPG_API USimplex : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:				

	UFUNCTION(BlueprintCallable)
		static float Simplex2D(FVector2D location, FVector2D peakLocation, float mountainLength = 5.0f, float heightPerBlock = 1.0f, float topRayonSurface = 0.0f);

	UFUNCTION(BlueprintCallable)
		static float Simplex2D_cos(FVector2D location, FVector2D peakLocation, float mountainLength = 5.0f, float heightPerBlock = 1.0f, float topRayonSurface = 0.0f);

	//UFUNCTION(BlueprintCallable)
	//	static float Simplex2D_expo(FVector2D location, FVector2D peakLocation, float mountainLength = 5.0f, float heightPerBlock = 1.0f, float topRayonSurface = 0.0f);
	//
	UFUNCTION(BlueprintCallable)
		static float SimplexDonut2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock);

	UFUNCTION(BlueprintCallable)
		static float SimplexArc2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock, float blockPerDegree, float rotation);
	
	UFUNCTION(BlueprintCallable)
		static float SimplexArcAttenuation2D(FVector2D location, FVector2D peakLocation, float circleRadius, float mountainRadius, float heightPerBlock, float blockPerDegree, float rotation, float flatnessHeight, float flatness);

	UFUNCTION(BlueprintCallable, Category="Simplex")
		static float GetMultiplePeaks1D(float location, float distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static float GetMultiplePeaksInCorner1D(float location, float distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static FVector2D GetMultiplePeaks2D(FVector2D location, FVector2D distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static FVector2D GetMultiplePeaksInCorner2D(FVector2D location, FVector2D distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static FVector GetMultiplePeaks3D(FVector location, FVector distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static FVector GetMultiplePeaksInCorner3D(FVector location, FVector distance);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Simplex")
		static FVector2D ErrorTolerance2D(FVector2D a, FVector2D errorTolerance);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dilation")
		static FVector2D Rectangle_Dilation2D(FVector2D peakLocation, FVector2D location, FVector2D distance);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dilation")
		static FVector2D Diagonale_Dilation2D(FVector2D peakLocation, FVector2D location, FVector2D distance);

	UFUNCTION(BlueprintCallable, Category = "Simplex")
		static float multiSimplex(TArray<FS_multiSimplex> list);

	UFUNCTION(BlueprintCallable, Category = "Simplex3D")
		static bool Simplex3D(FVector location, FVector peakLocation, float radius, FVector maxRadiusOnAxis);

	UFUNCTION(BlueprintCallable, Category = "Simplex3D")
		static bool SimplexDonut3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation);

	UFUNCTION(BlueprintCallable, Category = "Simplex3D")
		static bool SimplexArc3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation, float heightPerBlock);

	UFUNCTION(BlueprintCallable, Category = "Simplex3D")
		static bool SimplexArcAttenuation3D(FVector location, FVector peakLocation, float circleRadius, FVector caveRadiusOnAxis, float caveRadius, FRotator rotation, float heightPerBlock, float limit);

#pragma region "heightmap"

	UFUNCTION(BlueprintCallable, Category = "heightmap")
	static void zoom(UPARAM(ref) TArray<int32>& arr, UPARAM(ref) int32& size);
	UFUNCTION(BlueprintCallable, Category = "heightmap")
	static void FillBorders(UPARAM(ref) TArray<int32>& arr, const int32& size);
	UFUNCTION(BlueprintCallable, Category = "heightmap")
	static void DrawPointAtCenter(UPARAM(ref) TArray<int32>& arr);

#pragma endregion "heightmap"

};
