// Fill out your copyright notice in the Description page of Project Settings.

#include "PathFindingAlgorithmes.h"
#include "Engine/GameEngine.h"


//FNode3D UPathFindingAlgorithmes::AlgorithmA3D_Initialize(FIntVector location, int32 cost, int32 h)
//{
//	FNode3D start;
//	start.location = location;
//	start.cost = cost;
//	start.h = h;
//	return start;
//}
//
//FNode2D UPathFindingAlgorithmes::AlgorithmA2D_Initialize(FIntPoint location, int32 cost, int32 h)
//{
//	FNode2D start;
//	start.location = location;
//	start.cost = cost;
//	start.h = h;
//	return start;
//}

void UPathFindingAlgorithmes::AlgorithmA2D_ShortestPath(FNodeArray2D graph, FIntPoint goalloc, FIntPoint startloc, TArray<FIntPoint> moves, FIntPoint& nextMove, int32& timeToReach, FNodeArray2D& returnedGraph)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("start location : %d %d"), startloc.X, startloc.Y));

	FNode2D goal;				FNode2D start;
	goal.location = goalloc;	start.location = startloc;
	goal.cost = 0;				start.cost = 0;
	goal.h = 0;					start.h = 0;

	bool first = true;

	TArray<FIntPoint> closedlist;
	TArray<FNode2D> openlist; //(priorityqueue)
	openlist.Add(start);
	while (openlist.Num() > 0)
	//for (int j=0;j<100;j++)
	{
		FIntPoint currentlocation = openlist[0].location;
		openlist.HeapRemoveAt(0);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("current location : %d %d"), currentlocation.X, currentlocation.Y));

		int32 currentindex = currentlocation.X + currentlocation.Y*graph.ArraySize.X;

		if (currentlocation == goal.location)
		{
			nextMove = moves[graph.ArrayValues[currentindex].firstID];
			timeToReach = graph.ArrayValues[currentindex].cost;
			returnedGraph = graph;
			return;
			//return graph.ArrayValues[currentindex].cost;		//FINIT
		}


		//node2d neighbors = getneighbor(start,graph, moves);
		//for (fintpoint v : moves)
		for (int i = 0; i < moves.Num(); i++)
		{
			FIntPoint v = moves[i];
			v += currentlocation;
			int32 newindex = v.X + v.Y*graph.ArraySize.X; //+ v.z*graph.arraysize.x*graph.arraysize.y;
			//if (newindex >= 0 && newindex < graph.ArrayValues.Num())
			if (v.X > 0 && v.Y > 0 && v.X < graph.ArraySize.X && v.Y < graph.ArraySize.Y)
			{
				//fintpoint w = graph.arrayvalues[newindex].cost;
				bool bdothings = true;

				if (closedlist.Contains(graph.ArrayValues[newindex].location))
				{
					if (graph.ArrayValues[newindex].cost < graph.ArrayValues[currentindex].cost)
					{
						bdothings = false;
					}
				}

				bool b = false;
				for (FNode2D ru : openlist)
				{
					if (ru.location == graph.ArrayValues[newindex].location)
						b = true;
				}

				//if (openlist.Contains(graph.ArrayValues[newindex]))
				if (b)
				{
					if (graph.ArrayValues[newindex].cost < graph.ArrayValues[currentindex].cost)
					{
						bdothings = false;
					}
				}
				
				if (bdothings)
				{
					graph.ArrayValues[newindex].cost = graph.ArrayValues[currentindex].cost + graph.ArrayValues[newindex].hardness;
					graph.ArrayValues[newindex].h = graph.ArrayValues[newindex].cost + (graph.ArrayValues[newindex].location - goal.location).Size();
					if (!first)
						graph.ArrayValues[newindex].firstID = graph.ArrayValues[currentindex].firstID;
					else
						graph.ArrayValues[newindex].firstID = i;
					openlist.HeapPush(graph.ArrayValues[newindex]);
					//openlist.add(graph.arrayvalues[newindex]);
					//openlist.sort();
					//do things
				}

			}
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("%d"),graph.ArrayValues[currentindex].location);
		//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, (TEXT("Rotation: %f - %f - %f"), CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("location : %f %f"), graph.ArrayValues[currentindex].location.X, graph.ArrayValues[currentindex].location.Y));

		closedlist.Add(graph.ArrayValues[currentindex].location);
	}
	
	return;
}

//Node2D UPathFindingAlgorithmes::GetNeighbor(Node2D& start, FNodeArray2D& graph, TArray<FIntPoint>& moves)
//{
//	for (FIntPoint r : moves)
//	{
//		FIntPoint newLocation = start.location + r;	 
//		//if (newLocation.X < 0 || newLocation.Y < 0)
//	}
//	Node2D x;
//	return x;
//}



//Node3D UPathFindingAlgorithmes::Get(const FNodeArray3D Array, const int32 x, const int32 y, const int32 z)
//{
//	return Array.ArrayValues[x + y * Array.ArraySize.X + z * Array.ArraySize.X*Array.ArraySize.Y];
//}
//
//bool UPathFindingAlgorithmes::IsValid3D(const Node3D Array, const int32 x, const int32 y, const int32 z)
//{
//	int32 id = x + y * Array.ArraySize.X + z * Array.ArraySize.X*Array.ArraySize.Y;
//	if (id < 0 || id >= Array.ArrayValues.Num())
//		return false;
//	else
//		return true;
//}