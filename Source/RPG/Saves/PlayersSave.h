// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayersSave.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UPlayersSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform playerTransform;
	
	
};
