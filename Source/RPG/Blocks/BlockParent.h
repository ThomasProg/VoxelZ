// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RPG_API BlockParent
{
public:
	BlockParent();
	~BlockParent();						

	TMap<FString, FString> VString;
	TMap<FString, int32> VInt;

	TMap<FString, int32> Molecules;

};
