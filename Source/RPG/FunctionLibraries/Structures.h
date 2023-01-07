// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Structures.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FS_Identity
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SubRace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Job;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Title;
};

USTRUCT(BlueprintType)
struct FS_RaceDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Pros;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Cons;
};

USTRUCT(BlueprintType)
struct FS_Stats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float lifeRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float manaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float magicPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float magicArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;
};

USTRUCT(BlueprintType)
struct FS_Effects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText EffectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> Cumulated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> Tags;
};

USTRUCT(BlueprintType)
struct FS_Skills
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText SkilName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> EvolutionsID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> Tags;
};

USTRUCT(BlueprintType)
struct FS_Click
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntVector CaseLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CaseWorldLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CubeRelativeLocation;

};

USTRUCT(BlueprintType)
struct FS_SkillsStockage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FS_Click> Click;

};


USTRUCT(BlueprintType)
struct FS_Block
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 BlockType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector OriginLocation;
};

//USTRUCT(BlueprintType)
//struct FblockProperties
//{
//	GENERATED_BODY()
//public:
//	FIntVector location;
//	int32 blockType;
//
//	TMap<FString, FString> VString;
//	TMap<FString, int32> VInt;
//
//	TMap<FString, int32> Molecules;
//
//	//Default constructor
//	FblockProperties() : blockType(0) {}
//};

USTRUCT(BlueprintType)
struct FObjectProperties
{
	GENERATED_BODY()
public:
	//FIntVector originLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 blockType;

	//Default constructor
	FObjectProperties() : blockType(0) {}
};

USTRUCT(BlueprintType)
struct FSubObject : public FObjectProperties
{
	GENERATED_BODY()
public:
	FVector relativeLocation;	 //from 0.0 to 1.0 ; define the relative space in the cube
	FVector size;
};

USTRUCT(BlueprintType)
struct FblockProperties
{
	GENERATED_BODY()
public:

	//UPROPERTY(BlueprintReadWrite)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectProperties> Objects;

	//Default constructor
	//FblockProperties() : blockType(0) {}
};

//USTRUCT(BlueprintType)
//struct FS_Block
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<bool> SolidFace;		//for each face, give if it's solid (not drawn for opti if another face)
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool b3DModel = true;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TMap<FString, FString> VString;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TMap<FString, int32> VInt;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TMap<FString, int32> Molecules;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 BlockType;
//};

USTRUCT(BlueprintType)
struct FS_BlockChunkArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FblockProperties> ChunkField;
};

UENUM(BlueprintType)
enum EStructLocation
{
	VE_absoluteLocation			UMETA(DisplayName = "VE_absoluteLocation"),
	VE_relativeToNoise			UMETA(DisplayName = "VE_relativeToNoise"),
	VE_relativeToAnotherNoise 	UMETA(DisplayName = "VE_relativeToAnotherNoise"),
};

USTRUCT(BlueprintType)
struct FGeneratedStructs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EStructLocation> isRelative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntPoint AnotherLocation;
};

USTRUCT(BlueprintType)
struct FGeneratedStructs_Array
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGeneratedStructs> structs;
};


USTRUCT(BlueprintType)
struct FS_BlockChunkArrayLocated : public FS_BlockChunkArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FIntVector> ChunkFieldLocations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FGeneratedStructs> ChunkFieldOptions;
};

USTRUCT(BlueprintType)
struct FWaterToDo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FVector> localPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FIntVector chunkLoc;
};

UCLASS()
class RPG_API UStructures : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (CompactNodeTitle = "+"/*, Keywords = ("+")*/))
		static FS_Stats FS_Stats_add(FS_Stats a, FS_Stats b);

	UFUNCTION(BlueprintCallable,BlueprintPure,meta = (CompactNodeTitle = "-"/*,Keywords = ("-")*/))
		static FS_Stats FS_Stats_substract(FS_Stats a, FS_Stats b);
	
	UPROPERTY(BlueprintReadWrite)
		FVector WorldOriginOffset = FVector(0.0, 0.0, 0.0);

	UFUNCTION(BlueprintCallable,BlueprintPure)
		static int32 getFblockProperties(FblockProperties block);
};

