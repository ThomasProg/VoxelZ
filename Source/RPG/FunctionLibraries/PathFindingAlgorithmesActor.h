// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFindingAlgorithmesActor.generated.h"



USTRUCT(BlueprintType)
struct FActorNode2D
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntPoint location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 cost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		//int32 h;
		float h;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 firstID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 hardness;
};

USTRUCT(BlueprintType)
struct FActorNodeArray2D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FActorNode2D> ArrayValues;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntPoint ArraySize;
};

inline bool operator < (const FActorNode2D& lhs, const FActorNode2D& rhs)
{
	return lhs.h < rhs.h;
}

inline bool operator > (const FActorNode2D& lhs, const FActorNode2D& rhs)
{
	return lhs.h > rhs.h;
}


USTRUCT(BlueprintType)
struct FActorNode3D
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntVector location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 cost;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float h;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 firstID;
};

USTRUCT(BlueprintType)
struct FActorNodeArray3D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FActorNode3D> ArrayValues; //tarray<node3d>& arrayvalues;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FIntVector ArraySize;

	//fnodearray3d()
	//{

	//}

};

inline bool operator > (const FActorNode3D& lhs, const FActorNode3D& rhs)
{
	return lhs.h > rhs.h;	//>
}

inline bool operator < (const FActorNode3D& lhs, const FActorNode3D& rhs)
{
	return lhs.h < rhs.h;	  //<
}

UCLASS()
class RPG_API APathFindingAlgorithmesActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathFindingAlgorithmesActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TArray<FIntPoint> moves;
		FActorNodeArray2D graph;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FActorNodeArray3D graph3D;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		/*static*/ void AlgorithmA2D_ShortestPath(/*FActorNodeArray2D graph, */FIntPoint goalLoc, FIntPoint startLoc,
			FIntPoint& nextMove, int32& timeToReach, FActorNodeArray2D& returnedGraph);
	
	UFUNCTION(BlueprintCallable)
		/*static*/ void AlgorithmA3D_ShortestPath(FIntVector goalLoc, FIntVector startLoc,
			FIntVector& nextMove, int32& timeToReach, FActorNodeArray3D& returnedGraph);


	UFUNCTION(BlueprintNativeEvent)
		void forEachBlock(FIntPoint currentlocation, TArray<FIntPoint>& newPotentialLocations, TArray<int32>& hardness);
	virtual void forEachBlock_Implementation(FIntPoint currentlocation, TArray<FIntPoint>& newPotentialLocations, TArray<int32>& hardness);


	UFUNCTION(BlueprintNativeEvent)
		void forEachBlock3D(FIntVector currentlocation, TArray<FIntVector>& newPotentialLocations, TArray<int32>& hardness);
	virtual void forEachBlock3D_Implementation(FIntVector currentlocation, TArray<FIntVector>& newPotentialLocations, TArray<int32>& hardness);
};
