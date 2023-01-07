// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/SubReferences/Planet_Referential.h"
#include "Earth_Referential.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AEarth_Referential : public APlanet_Referential
{
	GENERATED_BODY()
	
public:
	//virtual int32 CalculateNoise_OneTime_Implementation(const FIntPoint& location) override;
	
	//virtual void GenerateBlock_OneTime(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, UPARAM(ref) TArray<FblockProperties>& chunk, int32 index) override;
	virtual void GenerateBlock_OneTime/*_Implementation*/(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)override;

	virtual int32 GenerateStruct_OneTime_Implementation(const FIntVector& location, const int32& noise, bool& isValidStruct) override;



	//UFUNCTION(BlueprintNativeEvent)
	//	void GenerateBlock_OneTime_BP(const FIntVector& relativeLocation, const FIntVector& worldLocation, const TArray <int32>& noiseArray, const TArray<FblockProperties>& chunk, const int32& index);
	//virtual void GenerateBlock_OneTime_BP_Implementation(const FIntVector& relativeLocation, const FIntVector& worldLocation, const TArray <int32>& noiseArray, const TArray<FblockProperties>& chunk, const int32& index);

	//UFUNCTION(BlueprintNativeEvent)
	//	int32 GenerateStruct_OneTime_BP(const FIntVector& location, const int32& noise, bool& isValidStruct);
	//virtual int32 GenerateStruct_OneTime_BP_Implementation(const FIntVector& location, const int32& noise, bool& isValidStruct);
	//
};
									 

//UPARAM(ref)
