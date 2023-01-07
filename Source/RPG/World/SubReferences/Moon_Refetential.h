// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/SubReferences/Planet_Referential.h"
#include "Moon_Refetential.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AMoon_Refetential : public APlanet_Referential
{
	GENERATED_BODY()
	
	virtual void GenerateBlock_OneTime(FIntVector relativeLocation, FIntVector worldLocation, const TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)override;

};
