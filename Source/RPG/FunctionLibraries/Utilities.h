// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structures.h"
#include "Utilities.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FS_FloatAndIntVectors
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector a;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntVector b;
};

UCLASS()
class RPG_API UUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure,meta=(CompactNodeTitle = "=="))
	static bool FIntVector_isEqual(FIntVector a, FIntVector b);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "!="))
	static bool FIntVector_isNotEqual(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = ">"))
	static bool FIntVector_greaterThan_FIntVector(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "."))
	static FVector FIntVector_to_FVector(FIntVector a);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "*"))
	static FVector FIntVector_times_FVector(FIntVector a, FVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "*"))
	static FIntVector FIntVector_times_FIntVector(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "-"))
	static FIntVector FIntVector_less_FIntVector(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "+"))
	static FIntVector FIntVector_plus_FIntVector(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "%"))
	static FIntVector FIntVector_modulo_FIntVector(FIntVector a, FIntVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "floor"))
	static FS_FloatAndIntVectors FVector_Floor(FVector a);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "ifLessAdd"))
		static float FIfNegativeAdd(float value, float toAdd);


	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		static float FFloatRange(float a, float b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		static FVector2D FVector2DRange(FVector2D a, FVector2D b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		static FVector FVectorRange(FVector a, FVector b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		int32 Fint32Range(int32 a, int32 b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		FIntPoint FIntPointRange(FIntPoint a, FIntPoint b);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "range"))
		FIntVector FIntVectorRange(FIntVector a, FIntVector b);
};
