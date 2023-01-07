// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectBase.h"
#include "MultiDimensionalArray.generated.h"

/**
 * 
 */

 //USTRUCT()
 //struct FArray3D
 //{
 //	GENERATED_BODY()
 //
 //public:
 //	//UPROPERTY(EditAnywhere)
 //	//TArray<UObjectBase> ArrayValues; //TArray<Node3D>& ArrayValues;				//UArrayProperty*
 //	//UPROPERTY(EditAnywhere)
 //	//FIntVector ArraySize;
 //};

UCLASS()
class RPG_API UMultiDimensionalArray : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		//UFUNCTION(BlueprintCallable, BlueprintPure)
		//UObjectBase Get(const FArray3D Array, const int32 x, const int32 y, const int32 z);

		//UFUNCTION(BlueprintCallable, BlueprintPure)
		//	bool IsValid(const FArray3D Array, const int32 x, const int32 y, const int32 z);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "3D Array")
		static int Get1DFrom3D(FIntVector a, FIntVector Size);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "3D Array")
		static FIntVector Get3DFrom1D(int32 a, FIntVector Size);
	
};
