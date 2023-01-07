// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "FunctionLibraries/Chunks.h"	
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Engine/GameEngine.h"
#include "FunctionLibraries/Chunks.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

AMyPlayerController::AMyPlayerController()
 {
 
     // do things
 
   //  static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Items/Blueprints/BP_ItemTest.BP_ItemTest'"));
   //  if (ItemBlueprint.Object){
		 //MyVoxelActor = (UClass*)ItemBlueprint.Object->GeneratedClass;
   //  }
 
 }

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ULocalPlayer* LocPlayer = Cast<ULocalPlayer>(Player);
	if (LocPlayer != nullptr)
		if (!LocPlayer->ViewportClient->Viewport || !LocPlayer->ViewportClient->Viewport->IsForegroundWindow())
		{
			// viewport is either not present or not in the foreground.
			savePlayerLocation();

		}


	DestroyChunks();
	SpawnVoxel();

	//switch (switchTick)
	//{
	//	case 0 :
	//	{
	//		DestroyChunks();
	//		switchTick = 1;
	//	}

	//	case 1:
	//	{
	//		SpawnVoxel();
	//		switchTick = 0;
	//	}

		//case 2:
		//{
		//	if (lastVoxel->chunkFields.Num() != 0)
		//		lastVoxel->UpdateMesh();
		//	//lastVoxel->UpdateMeshTextures();
		//	//lastVoxel->bInitialized = true;
		//	switchTick = 0;
		//}
	//}
	//NewChunks();

}

AVoxelActor* AMyPlayerController::Start_Implementation(FS_ChunkProperties location, AWorldContainer* ref)
{
	//AVoxelActor* x;
	AVoxelActor* w = GetWorld()->SpawnActor<AVoxelActor>(FVector(0.0,0.0,0.0), FRotator(0.0f, 0.0f, 0.0f));
	return w;
}

void AMyPlayerController::savePlayerLocation_Implementation()
{
	return;
}

void AMyPlayerController::SpawnVoxel()
{
	//FS_FindChunk rp;
	//rp = UChunks::Search(ChunksLocation, LastLocation);
	//if (!rp.Found)
	//{
	//	FS_ChunkProperties v; v.location = FVector(LastLocation) * FVector(ChunkLineElements) * CubeSize; v.Coordonates = LastLocation;
	//	AVoxelActor* w = Start(v); 
	//	w->chunkLineElements = this->ChunkLineElements;
	//	ChunksRef.Insert(w, rp.index);
	//	ChunksLocation.Insert(LastLocation, rp.index);
	//}
	//else
	do
	{
		//for (AWorldContainer* ref : referentials)
		for (int i=0;i<referential.Num();i++)
		{	
			AWorldContainer*& ref = referential[i];
			FS_EachReferencialChunk_Management& chunk = chunksManagement[i];

			if (chunk.ChunksToSpawn.Num() > 0)
			{
				FS_FindChunk r;
				r = UChunks::Search(chunk.ChunksLocation, chunk.ChunksToSpawn[0].Coordonates);

				if (r.Found)
				{
					do
					{
						chunk.ChunksToSpawn.RemoveAt(0);
						if (chunk.ChunksToSpawn.Num() > 0)
							r = UChunks::Search(chunk.ChunksLocation, chunk.ChunksToSpawn[0].Coordonates);
					} while (r.Found && chunk.ChunksToSpawn.Num() > 0);
					//SpawnVoxel();
				}

				if (chunk.ChunksToSpawn.Num() > 0) //else
				{
					//Start(ChunksToSpawn[0].Coordonates);

					//AVoxelActor* w = GetWorld()->SpawnActor<AVoxelActor>(MyVoxelActor,ChunksToSpawn[0].location, FRotator(0.0f, 0.0f, 0.0f));
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Voxel Spawned"));

					/*AVoxelActor* w*/lastVoxel = Start(chunk.ChunksToSpawn[0], ref); //ChunksToSpawn[0].Coordonates);
					//lastVoxel->chunkLineElements = ref->chunkLineElements;
					//lastVoxel->referential = ref;
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Chunks Spawned"));
						//w->ChunkCoordonates = ChunksToSpawn[0].Coordonates;
						if (r.index >= chunk.ChunksRef.Num())
							chunk.ChunksRef.Add(lastVoxel);
						else
							chunk.ChunksRef.Insert(lastVoxel, r.index);
					chunk.ChunksLocation.Insert(chunk.ChunksToSpawn[0].Coordonates, r.index);
					chunk.ChunksToSpawn.RemoveAt(0);
					//ChunksRef[r.index]->Load();

					//if (ChunksRef[r.index]->chunkFields.Num() != 0)
					//	ChunksRef[r.index]->UpdateMesh();

				}
			}
			SpawningNb = SpawningNb <= 0 ? 0 : SpawningNb - 1;
		}

	} while (SpawningNb > 0);
}

void AMyPlayerController::DestroyChunks()
{
	APlayerCharacter* Pawn = Cast<APlayerCharacter>(this->GetPawn());
	if (Pawn)
	{
		//for (AWorldContainer* ref : referentials)
		for (int i = 0; i<referential.Num(); i++)
		{
			AWorldContainer*& ref = referential[i];
			FS_EachReferencialChunk_Management& chunk = chunksManagement[i];

			FVector loc = ref->GetActorRotation().UnrotateVector(Pawn->GetActorLocation() + FVector(UGameplayStatics::GetWorldOriginLocation(this->GetWorld()))) - ref->GetActorLocation();

			FS_FloatAndIntVectors p = UChunks::GetChunk(FVector(ref->chunkLineElements), ref->cubeSize, loc);
			//p.b = FIntVector(ref->GetActorRotation().UnrotateVector(FVector(p.b)));

			if (p.b != chunk.lastPlayerChunk)
			{
				chunk.lastPlayerChunk = p.b;
				NewChunkLocation(ref);
				if (chunk.ChunksLocation.Num() > 0)
				{
					//int i = ChunksLocation.Num()-1;
					////for (int i = 0; i < ChunksLocation.Num(); i++)
					//while (i>=0)
					//{
					//	FIntVector ra = p.b - ChunksLocation[i];
					//	//if (FMath::Abs(ra.X) > range + 1 || FMath::Abs(ra.Y) > range + 1 || FMath::Abs(ra.Z) > range + 1)
					//	if (ra.Size() > range + 2)
					//	{
					//		if (ChunksRef[i])
					//		{
					//			ChunksRef[i]->Destroy();
					//			ChunksRef.RemoveAt(i);
					//			ChunksLocation.RemoveAt(i);
					//		}
					//		i--;
					//	}
					//	else
					//		break;
					//}

					int i = 0;
					//for (int i = 0; i < ChunksLocation.Num(); i++)
					while (i < chunk.ChunksLocation.Num())
					{
						FIntVector ra = p.b - chunk.ChunksLocation[i];
						//if (FMath::Abs(ra.X) > range + 1 || FMath::Abs(ra.Y) > range + 1 || FMath::Abs(ra.Z) > range + 1)
						//if (frange > (chunk.ChunksRef[i]->GetActorLocation() + chunk.ChunksRef[i]->FvoxelSize*(FVector(chunk.ChunksRef[i]->chunkLineElements)/2) - loc).Size)
						if (frange*2.0f < ((chunk.ChunksRef[i]->GetActorLocation() - loc)).Size())	 	 
						{
							if (chunk.ChunksRef[i])
							{
								chunk.ChunksRef[i]->Destroy();
								chunk.ChunksRef.RemoveAt(i);
								chunk.ChunksLocation.RemoveAt(i);
							}
						}
						else
							i++;
					}
				}



				if (chunk.ChunksToSpawn.Num() > 0)
				{
					int i = chunk.ChunksToSpawn.Num() - 1;
					//for (int i = 0; i < ChunksLocation.Num(); i++)
					while (i >= 0)
					{
						FIntVector ra = p.b - chunk.ChunksToSpawn[i].Coordonates;
						//if (FMath::Abs(ra.X) > range + 1 || FMath::Abs(ra.Y) > range + 1 || FMath::Abs(ra.Z) > range + 1)
						//if ((chunk.ChunksToSpawn[i].Coordonates - p.b).Size() > range + 2)
						if (frange*1.5f < (chunk.ChunksToSpawn[i].location - loc).Size())
						{
							chunk.ChunksToSpawn.RemoveAt(i);
							i--;
						}
						else
							break;
					}

					//int i = 0;
					////for (int i = 0; i < ChunksToSpawn.Num(); i++)
					//while (i<ChunksToSpawn.Num())
					//{
					//	//if ((FVector(ChunksToSpawn[i].location) - Pawn->GetActorLocation()).Size() > range * 200 * 10*2)
					//	FIntVector ra = p.b - ChunksToSpawn[i].Coordonates;
					//	if (FMath::Abs(ra.X) > range + 1 || FMath::Abs(ra.Y) > range + 1 || FMath::Abs(ra.Z) > range + 1)
					//	{
					//		ChunksToSpawn.RemoveAt(i);
					//		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Chunk removed 2"));
					//	}
					//	else
					//		i++;
					//}

					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Chunks destroyed"));
				}

				//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Calling NewChunks"));
				NewChunks();
			}

		}
	}
}

void AMyPlayerController::NewChunks()									 //TODO : put ChunkToSpawn and ChunksLocation in the WorldContainer : interferences between chunks with the same coordonates of two different referentials
{
	APlayerCharacter* Pawn = Cast<APlayerCharacter>(this->GetPawn());
	if (Pawn)
	{
		//for (AWorldContainer* ref : referentials)
		for (int i = 0; i<referential.Num(); i++)
		{
			AWorldContainer*& ref = referential[i];
			FS_EachReferencialChunk_Management& chunk = chunksManagement[i];

			for (int x = chunk.lastPlayerChunk.X - range.X; x <= chunk.lastPlayerChunk.X + range.X; x++)
			{
				for (int y = chunk.lastPlayerChunk.Y - range.Y; y <= chunk.lastPlayerChunk.Y + range.Y; y++)
				{
					for (int z = chunk.lastPlayerChunk.Z - range.Z; z <= chunk.lastPlayerChunk.Z + range.Z; z++)
					{
						bool bNewChunk;
						if (chunk.isLimited)
						{
							FS_FindChunk t;
							t = UChunks::Search(ref->chunkCoordonates, FIntVector(x, y, z));
							bNewChunk = t.Found;													
						}
						else
							bNewChunk = true;

						if (bNewChunk)
						{
							FS_FindChunk r;
							r = UChunks::Search(chunk.ChunksLocation, FIntVector(x, y, z));
							bool doYourJob = true;
							for (FS_ChunkProperties q : chunk.ChunksToSpawn)
							{
								if (q.Coordonates == FIntVector(x, y, z))
									doYourJob = false;
							}

							if (!r.Found && GetPawn() != nullptr && doYourJob)
							{
								FS_ChunkProperties v;
								v.Coordonates = FIntVector(x, y, z);
								v.location = ref->GetActorRotation().RotateVector(FVector(x, y, z) * FVector(ref->chunkLineElements) * ref->cubeSize) + ref->GetActorLocation();	  //FVector loc = ref->GetActorRotation().UnrotateVector(Pawn->GetActorLocation() + FVector(UGameplayStatics::GetWorldOriginLocation(this->GetWorld())));
								if (v.Coordonates.X == chunk.lastPlayerChunk.X &&  v.Coordonates.Y == chunk.lastPlayerChunk.Y && v.Coordonates.Z == chunk.lastPlayerChunk.Z)
									chunk.ChunksToSpawn.Insert(v,0);
								else
									chunk.ChunksToSpawn.Add(v);

								//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Chunks added"));


								//FVector PlayerLoc = Pawn->GetActorLocation() - ref->cubeSize*(FVector(ref->chunkLineElements)/2.0);

								//sort(ChunksToSpawn.begin(), ChunksToSpawn.end(),
								//	[](const FS_ChunkProperties & a, const FS_ChunkProperties & b) -> bool
								//{
								//	return (Pawn->GetActorLocation()-a.location).Size > (Pawn->GetActorLocation() - b.location).Size();
								//});



								//if ((FVector(v.location) - GetPawn()->GetActorLocation() - FVector(0.0,0.0,-600)).Size() < 2900)

								//float playerL = (Pawn->GetActorLocation() - v.location).Size();//(UChunks::GetChunk(FVector(ChunkLineElements), CubeSize, Pawn->GetActorLocation()).b);


								//float diffL = (Pawn->GetActorLocation() - v.location).Size();

								//int32 id = 0;

								//if (ChunksToSpawn.Num()>0)
								//{
								//	while ((Pawn->GetActorLocation() - ChunksToSpawn[id].location).Size() < diffL)
								//	{
								//		id++;
								//		if (id >= ChunksToSpawn.Num())
								//			break;
								//	}

								//}
								//ChunksToSpawn.Insert(v, id);



								//if (FMath::Abs(ra.X) < 2 && FMath::Abs(ra.Y) < 2 && FMath::Abs(ra.Z) < 2)
								//{
								//	ChunksToSpawn.Insert(v, 0);
								//	SpawningNb++;
								//	//if (v.Coordonates == LastLocation)
								//	//{
								//	SpawnVoxel();
								//	//}
								//}
								//else
								//{
								//	ChunksToSpawn.Add(v);

								//	//if (/*bDoOnce*/false)
								//	//{
								//	//	SpawnVoxel();
								//	//}
								//	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Chunk Added"));
								//}

							}
						
						}
					}
				}
			}
			//bDoOnce = false;

			////FVector PlayerLoc = Pawn->GetActorLocation();// - ref->cubeSize*(FVector(ref->chunkLineElements) / 2.0);
			////chunk.ChunksToSpawn.Sort([&](const FS_ChunkProperties& a, const FS_ChunkProperties& b)
			////{
			////	//return ((PlayerLoc - a.location)*frangeFocus).Size() < ((PlayerLoc - b.location)*frangeFocus).Size();
			////	//return (FVector::DotProduct(PlayerLoc - a.location,frangeFocus) < FVector::DotProduct(PlayerLoc - b.location,frangeFocus));
			////	//FVector pl = PlayerLoc - a.location;
			////	//return (abs(pl.X*frangeFocus.X) + abs(pl.Y*frangeFocus.Y) + abs(pl.Y*frangeFocus.Y));


			////	//FRotator fr = UKismetMathLibrary::FindLookAtRotation(frangeFocus, a.location - PlayerLoc);
			////	//if (fr.Pitch > 180)
			////	//	fr.Pitch = 360 - fr.Pitch;
			////	//if (fr.Yaw > 180)
			////	//	fr.Yaw = 360 - fr.Yaw;
			////	//if (fr.Roll > 180)
			////	//	fr.Roll = 360 - fr.Roll;
			////	//FRotator fs = UKismetMathLibrary::FindLookAtRotation(frangeFocus, b.location - PlayerLoc);
			////	//if (fs.Pitch > 180)
			////	//	fr.Pitch = 360 - fr.Pitch;
			////	//if (fs.Yaw > 180)
			////	//	fr.Yaw = 360 - fr.Yaw;
			////	//if (fs.Roll > 180)
			////	//	fr.Roll = 360 - fr.Roll;
			////	//return (fr.Pitch + fr.Yaw + fr.Roll + (PlayerLoc - a.location).Size()*frangeMulti < fs.Pitch + fs.Yaw + fs.Roll + (PlayerLoc - b.location).Size()*frangeMulti);

			////	float bl1 = (FVector::CrossProduct((PlayerLoc - a.location),frangeFocus)).Size() / (frangeFocus).Size();
			////	float bl2 = (FVector::CrossProduct((PlayerLoc - b.location),frangeFocus)).Size() / (frangeFocus).Size();

			////	return ((PlayerLoc - a.location)).Size()*frangeMulti + bl1 < ((PlayerLoc - b.location)).Size()*frangeMulti + bl2;
			////});
		}

	}
}

void AMyPlayerController::NewChunkLocation_Implementation(AWorldContainer* ref)
{
	return;
}

void AMyPlayerController::AddReferential(AWorldContainer* ref, bool isLimited)
{
	referential.Add(ref);
	FS_EachReferencialChunk_Management w; 
	w.isLimited = isLimited;
	chunksManagement.Add(w);
}

void AMyPlayerController::SetReferentials(TArray<AWorldContainer*> ref)
{
	referential = ref;
	chunksManagement.SetNumZeroed(ref.Num());
}

void AMyPlayerController::SortChunksToSpawn()
{
	APlayerCharacter* Pawn = Cast<APlayerCharacter>(this->GetPawn());
	if (Pawn)
	{
		for (int i = 0; i < referential.Num(); i++)
		{
			AWorldContainer*& ref = referential[i];
			FS_EachReferencialChunk_Management& chunk = chunksManagement[i];

			FVector PlayerLoc = Pawn->GetActorLocation();
			chunk.ChunksToSpawn.Sort([&](const FS_ChunkProperties& a, const FS_ChunkProperties& b)
			{
				float bl1 = (FVector::CrossProduct((PlayerLoc - a.location), frangeFocus)).Size() / (frangeFocus).Size();
				float bl2 = (FVector::CrossProduct((PlayerLoc - b.location), frangeFocus)).Size() / (frangeFocus).Size();

				return ((PlayerLoc - a.location)).Size()*frangeMulti + bl1 < ((PlayerLoc - b.location)).Size()*frangeMulti + bl2;
			});
		}
	}
}