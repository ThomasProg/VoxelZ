// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structures.h"
#include "Inventory.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FS_InventorySkill
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FblockProperties block;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName blockID;
};

UCLASS()
class RPG_API UInventory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
