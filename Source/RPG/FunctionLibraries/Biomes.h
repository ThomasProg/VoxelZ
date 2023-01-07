// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Biomes.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UBiomes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	float Humidity(FIntVector Coordonates);

	float AverageTemperature(FIntVector Coordonates);
public:
	UFUNCTION(BlueprintCallable)
	static int32 GetBiomeYAxis(int32 Y);
	UFUNCTION(BlueprintCallable)
	static int32 GetBiomeYZAxisAboveSurface(FIntVector Coordonates);
	UFUNCTION(BlueprintCallable)
	static int32 GetBiomeYZAxisBelowSurface(FIntVector Coordonates, float Surface);

	UFUNCTION(BlueprintCallable)
		static float TemperatureWithAltitude(int32 Z);
	UFUNCTION(BlueprintCallable)
		static float AtmosphericPression(int32 Z, float Kelvin);
	UFUNCTION(BlueprintCallable,BlueprintPure)
		static float CelsiusToKelvin(float Celsius);
};
