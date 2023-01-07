// Fill out your copyright notice in the Description page of Project Settings.

#include "PathFindingAlgorithmesActor.h"
#include "Engine/GameEngine.h"


// Sets default values
APathFindingAlgorithmesActor::APathFindingAlgorithmesActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathFindingAlgorithmesActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathFindingAlgorithmesActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APathFindingAlgorithmesActor::AlgorithmA2D_ShortestPath(FIntPoint goalloc, FIntPoint startloc, FIntPoint& nextMove, int32& timeToReach, FActorNodeArray2D& returnedGraph)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("start location : %d %d"), startloc.X, startloc.Y));

	FActorNode2D goal;			FActorNode2D start;
	goal.location = goalloc;	start.location = startloc;
	goal.cost = 0;				start.cost = 0;
	goal.h = 0.0f;				start.h = 0.0f;

	bool first = true;

	TArray<FIntPoint> closedlist;
	TArray<FActorNode2D> openlist; //(priorityqueue)
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
			//nextMove = moves[graph.ArrayValues[currentindex].firstID];
			timeToReach = graph.ArrayValues[currentindex].cost;
			returnedGraph = graph;
			//return graph.ArrayValues[currentindex].firstID;
			//return graph.ArrayValues[currentindex].cost;		//FINIT
			return;
		}


		//node2d neighbors = getneighbor(start,graph, moves);
		//for (fintpoint v : moves)

		TArray<int32> hardness;
		TArray<FIntPoint> moves;
		forEachBlock(currentlocation, moves, hardness);

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
					if (graph.ArrayValues[newindex].cost < graph.ArrayValues[currentindex].cost + hardness[i])	  // >
					{
						bdothings = false;
					}
				}

				bool b = false;
				for (FActorNode2D ru : openlist)
				{
					if (ru.location == graph.ArrayValues[newindex].location)
						b = true;
				}

				//if (openlist.Contains(graph.ArrayValues[newindex]))
				if (b)
				{
					if (graph.ArrayValues[newindex].cost < graph.ArrayValues[currentindex].cost + hardness[i])   // <
					{
						bdothings = false;
					}
				}

				if (bdothings)
				{
					graph.ArrayValues[newindex].cost = graph.ArrayValues[currentindex].cost + hardness[i];//+ graph.ArrayValues[newindex].hardness;
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

void APathFindingAlgorithmesActor::forEachBlock_Implementation(FIntPoint currentlocation, TArray<FIntPoint>& newPotentialLocations, TArray<int32>& hardness)
{
	return;
}



void APathFindingAlgorithmesActor::AlgorithmA3D_ShortestPath(FIntVector goalLoc, FIntVector startLoc,FIntVector& nextMove, int32& timeToReach, FActorNodeArray3D& returnedGraph)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("start location : %d %d"), startloc.X, startloc.Y));

	FActorNode3D goal;			FActorNode3D start;
	goal.location = goalLoc;	start.location = startLoc;
	goal.cost = 0;				start.cost = 0;
	goal.h = 0.0f;				start.h = 0.0f;

	bool first = true;

	int32 debugIndex = 0;

	TArray<FIntVector> closedlist;
	TArray<FActorNode3D> openlist; //(priorityqueue)
	openlist.Add(start);
	while (openlist.Num() > 0)
		//for (int j=0;j<100;j++)
	{
		FIntVector currentlocation = openlist[0].location;
		openlist.HeapRemoveAt(0);

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("current location : %d %d %d"), currentlocation.X, currentlocation.Y, currentlocation.Z));

		int32 currentindex = currentlocation.X + currentlocation.Y*graph3D.ArraySize.X + currentlocation.Z*graph3D.ArraySize.X*graph3D.ArraySize.Y;

		if (currentlocation == goal.location)
		{
			//nextMove = moves[graph.ArrayValues[currentindex].firstID];
			timeToReach = graph3D.ArrayValues[currentindex].cost;
			returnedGraph = graph3D;
			//return graph.ArrayValues[currentindex].firstID;
			//return graph.ArrayValues[currentindex].cost;		//FINIT
			return;
		}


		//node2d neighbors = getneighbor(start,graph, moves);
		//for (fintpoint v : moves)

		TArray<int32> hardness;
		TArray<FIntVector> moves;
		forEachBlock3D(currentlocation, moves, hardness);

		for (int i = 0; i < moves.Num(); i++)
		{
			FIntVector v = moves[i];
			v += currentlocation;
			int32 newindex = v.X + v.Y*graph3D.ArraySize.X + v.Z*graph3D.ArraySize.X*graph.ArraySize.Y;
														  //if (newindex >= 0 && newindex < graph.ArrayValues.Num())
			if (v.X > 0 && v.Y > 0 && v.Z > 0 && v.X < graph3D.ArraySize.X && v.Y < graph3D.ArraySize.Y &&  v.Z < graph3D.ArraySize.Z)
			{
				//fintpoint w = graph.arrayvalues[newindex].cost;
				bool bdothings = true;

				if (closedlist.Contains(graph3D.ArrayValues[newindex].location))
				{
					//if (graph3D.ArrayValues[newindex].cost > graph3D.ArrayValues[currentindex].cost + hardness[i])
					if (graph3D.ArrayValues[newindex].cost < graph3D.ArrayValues[currentindex].cost + hardness[i])
					{
						bdothings = false;
					}
				}

				bool b = false;
				for (FActorNode3D ru : openlist)
				{
					if (ru.location == graph3D.ArrayValues[newindex].location)
						b = true;
				}

				//if (openlist.Contains(graph.ArrayValues[newindex]))
				if (b)
				{
					if (graph3D.ArrayValues[newindex].cost < graph3D.ArrayValues[currentindex].cost + hardness[i])	 // >
					{
						bdothings = false;
					}
				}

				if (bdothings)
				{
					//if (newindex < graph3D.ArrayValues.Num() && currentindex < graph3D.ArrayValues.Num() && i < hardness.Num())				 //No error mod
					//{
						graph3D.ArrayValues[newindex].cost = graph3D.ArrayValues[currentindex].cost + hardness[i]; // if a crash occurs, look in forEachBlock3D if hardness.Num() >= NewPotentialLocations.Num()
						graph3D.ArrayValues[newindex].h = graph3D.ArrayValues[newindex].cost + (graph3D.ArrayValues[newindex].location - goal.location).Size();
						if (!first)
							graph3D.ArrayValues[newindex].firstID = graph3D.ArrayValues[currentindex].firstID;
						else
							graph3D.ArrayValues[newindex].firstID = i;

						//if (debugIndex < 1050)
						//{
							openlist.HeapPush(graph3D.ArrayValues[newindex]);
							debugIndex++;
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("current location")));
						//}
					//	//openlist.add(graph.arrayvalues[newindex]);
					//	//openlist.sort();
					//	//do things
					//}

				}

			}
		}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("start location : %d %d %d"), graph3D.ArrayValues[currentindex].location.X, graph3D.ArrayValues[currentindex].location.Y, graph3D.ArrayValues[currentindex].location.Z));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("%d"),graph.ArrayValues[currentindex].location);
		//GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Yellow, (TEXT("Rotation: %f - %f - %f"), CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("location : %f %f"), graph.ArrayValues[currentindex].location.X, graph.ArrayValues[currentindex].location.Y));

		closedlist.Add(graph3D.ArrayValues[currentindex].location);
	}

	returnedGraph = graph3D;

	return;
}

void APathFindingAlgorithmesActor::forEachBlock3D_Implementation(FIntVector currentlocation, TArray<FIntVector>& newPotentialLocations, TArray<int32>& hardness)
{
	return;
}


