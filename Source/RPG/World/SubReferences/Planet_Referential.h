// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/WorldContainer.h"
#include "Planet_Referential.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API APlanet_Referential : public AWorldContainer
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Planet")
	float gravityScale;

};
