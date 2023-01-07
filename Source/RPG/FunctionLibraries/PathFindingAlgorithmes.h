// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PathFindingAlgorithmes.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FNode3D
{
public:
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntVector location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 cost; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 h;

	//FNode3D()
	//{
	//	cost = 0; h = 0;
	//}
	//inline bool operator == (const FNode3D& lhs, const FNode3D& rhs)
	//{//We need to overload "<" to put our struct into a set
	//	return lhs.cost == rhs.cost;
	//}

};

USTRUCT(BlueprintType)
struct FNode2D
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint location;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 cost; 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 h;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 firstID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 hardness;

	//FNode2D()
	//{
	//	cost = 0; h = 0;
	//}
	//inline bool operator == (const FNode2D& lhs)
	//{//We need to overload "<" to put our struct into a set
	//	return lhs.cost == this->cost;
	//}
};






//
//inline void operator = (const Node3D& a, const Node3D& b)
//{
//	
//}
//
//inline void operator = (const Node2D& a, const Node2D& b)
//{
//	
//}



//static bool isValid(int x, int y) { //If our Node is an obstacle it is not valid
//	int id = x + y * (X_MAX / X_STEP);
//	if (world.obstacles.count(id) == 0) {
//		if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP)) {
//			return false;
//		}
//		return true;
//	}
//	return false;
//}

USTRUCT(BlueprintType)
struct FNodeArray2D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNode2D> ArrayValues;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntPoint ArraySize;

	//FNodeArray2D()
	//{
	//	//ArraySize = FIntPoint(;
	//}

	//inline bool operator == (const FNode2D& lhs, const FNode2D& rhs)
	//{//We need to overload "<" to put our struct into a set
	//	return lhs.cost == rhs.cost;
	//}
};

USTRUCT(BlueprintType)
struct FNodeArray3D
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNode3D> arrayvalues; //tarray<node3d>& arrayvalues;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FIntVector arraysize;

	//fnodearray3d()
	//{

	//}

};

inline bool operator < (const FNode3D& lhs, const FNode3D& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.h < rhs.h;
}

inline bool operator < (const FNode2D& lhs, const FNode2D& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.h < rhs.h;
}

inline bool operator > (const FNode3D& lhs, const FNode3D& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.h > rhs.h;
}

inline bool operator > (const FNode2D& lhs, const FNode2D& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.h > rhs.h;
}

//inline bool operator == (const FNode3D& lhs, const FNode3D& rhs)
//{//We need to overload "<" to put our struct into a set
//	return lhs.cost == rhs.cost;
//}
//
//inline bool operator == (const FNode2D& lhs, const FNode2D& rhs)
//{//We need to overload "<" to put our struct into a set
//	return lhs.cost == rhs.cost;
//}



UCLASS()
class RPG_API UPathFindingAlgorithmes : public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()


	//static FNode3D AlgorithmA3D_Initialize(FIntVector location, int32 cost=0, int32 h=0);

	////static void AlgorithmA3D_ShortestPath(FNodeArray3D graph, Node3D goal, Node3D start, TArray<FIntVector> moves);



	//static FNode2D AlgorithmA2D_Initialize(FIntPoint location, int32 cost = 0, int32 h = 0);

	//static void AlgorithmA2D_ShortestPath(TArray<Node2D> graph, Node2D goal, Node2D start,
	//	TArray<FIntPoint> moves = { FIntPoint(1,0),FIntPoint(-1,0),FIntPoint(0,-1),FIntPoint(0,1) });

	UFUNCTION(BlueprintCallable)
		static void AlgorithmA2D_ShortestPath(FNodeArray2D graph, FIntPoint goalLoc, FIntPoint startLoc,
			TArray<FIntPoint> moves, FIntPoint& nextMove, int32& timeToReach, FNodeArray2D& returnedGraph); //= { FIntPoint(1,0),FIntPoint(-1,0),FIntPoint(0,-1),FIntPoint(0,1) });

	//UFUNCTION(BlueprintCallable)
	//static int32 AlgorithmA2D_ShortestPath2(FNodeArray2D graph, FIntVector arraysize, FIntPoint goalLoc, FIntPoint startLoc,
	//	TArray<FIntPoint> moves); //= { FIntPoint(1,0),FIntPoint(-1,0),FIntPoint(0,-1),FIntPoint(0,1) });
	
	//static Node2D GetNeighbor(Node2D& start, FNodeArray2D& graph, TArray<FIntPoint>& moves);

	

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//	Node3D* Get3D(const FNodeArray3D Array, const int32 x, const int32 y, const int32 z);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//	bool IsValid3D(const FNodeArray3D Array, const int32 x, const int32 y, const int32 z);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//	Node3D* Get3d(const FNodeArray3D Array, const int32 x, const int32 y, const int32 z);

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//	bool IsValid3D(const Node3D Array, const int32 x, const int32 y, const int32 z);
};
