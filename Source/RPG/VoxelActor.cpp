// Fill out your copyright notice in the Description page of Project Settings.

#include "VoxelActor.h"

#include "FunctionLibraries/Chunks.h"
#include "Engine.h"
#include "Saves/ChunkSave.h"
#include "FunctionLibraries/Simplex.h"
#include "Kismet/GameplayStatics.h"
//#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"



const int32 bTriangles[] = { 2,1,0,0,3,2 };
const FVector2D bUVs[] = { FVector2D(0.000000,0.000000),FVector2D(0.000000,0.100000),FVector2D(0.100000,0.100000),FVector2D(0.100000,0.000000) };
const FVector bNormals0[] = { FVector(0,0,1),FVector(0,0,1),FVector(0,0,1),FVector(0,0,1) };
const FVector bNormals1[] = { FVector(0,0,-1),FVector(0,0,-1),FVector(0,0,-1),FVector(0,0,-1) };
const FVector bNormals2[] = { FVector(0,1,0),FVector(0,1,0),FVector(0,1,0),FVector(0,1,0) };
const FVector bNormals3[] = { FVector(0,-1,0),FVector(0,-1,0),FVector(0,-1,0),FVector(0,-1,0) };
const FVector bNormals4[] = { FVector(1,0,0),FVector(1,0,0),FVector(1,0,0),FVector(1,0,0) };
const FVector bNormals5[] = { FVector(-1,0,0),FVector(-1,0,0),FVector(-1,0,0),FVector(-1,0,0) };
const FVector bMask[] = { FVector(0.000000,0.000000,1.000000), FVector(0.000000,0.000000,-1.000000),FVector(0.000000,1.000000,0.000000),FVector(0.000000,-1.000000,0.000000) ,FVector(1.000000,0.000000,0.000000) ,FVector(-1.000000,0.000000,0.000000) };


// Sets default values
AVoxelActor::AVoxelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Assets/MyVoxelActor.MyVoxelActor'"));
	//if (ItemBlueprint.Object) {
	//	MyVoxelActor = (UClass*)ItemBlueprint.Object->GeneratedClass;
	//}
	FvoxelSizeHalf.X = 200; FvoxelSizeHalf.Y = 200; FvoxelSizeHalf.Z = 200;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("OBJRoot"));



	FString string = "Voxel_" + FString::FromInt(ChunkCoordonates.X) + "_" + FString::FromInt(ChunkCoordonates.Y) + "_" + FString::FromInt(ChunkCoordonates.Z);
	FName name = FName(*string);

	URuntimeMeshComponent* a = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("1"));			//ConstructObject<URuntimeMeshComponent>(CompClass, this, YourObjectName);
	runTimeComponents.Add(a);
	URuntimeMeshComponent* b = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("2"));
	runTimeComponents.Add(b);
	//runTimeComponents.Add(NewObject<URuntimeMeshComponent>(this, name));
	//runTimeComponents.Add(NewObject<URuntimeMeshComponent>(this, name));

	for (URuntimeMeshComponent* runTimeComponent : runTimeComponents)
	{
		if (runTimeComponent)	 //isnotvalid, bug
		{
			runTimeComponent->SetupAttachment(RootComponent);
		}
	}
}

// Called when the game starts or when spawned
void AVoxelActor::BeginPlay()
{
	Super::BeginPlay();
	
	//if (fields.Num == 0)
	//{
	//	for (int i = 0; i < chunkTotalElements; i++)
	//	{
	//		FblockProperties w;
	//		fields.Add(w);
	//	}
	//}

	Load(chunkFields, ChunkCoordonates);
	if (chunkFields.Num() != 0)
		UpdateMesh();
}

// Called every frame
void AVoxelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoxelActor::OnConstruction(const FTransform & Transform)
{
	//chunkZElements = 80;
	chunkTotalElements = chunkLineElements.X * chunkLineElements.Y * chunkLineElements.Z;
	//chunkLineElementsP2 = chunkLineElements * chunkLineElements;
	//voxelSizeHalf = voxelSize / 2;
	FvoxelSizeHalf = FvoxelSize / 2;

	//FString string = "Voxel_" + FString::FromInt(ChunkCoordonates.X) + "_" + FString::FromInt(ChunkCoordonates.Y) + "_" + FString::FromInt(ChunkCoordonates.Z);
	//FName name = FName(*string);
	//proceduralComponent = NewObject<UProceduralMeshComponent>(this, name);
	//proceduralComponent->RegisterComponent();
	//RootComponent->SetWorldTransform(Transform); //set position

	//URuntimeMeshComponent* a = NewObject<URuntimeMeshComponent>(this, "1");			//ConstructObject<URuntimeMeshComponent>(CompClass, this, YourObjectName);
	//runTimeComponents.Add(a);
	//URuntimeMeshComponent* b = NewObject<URuntimeMeshComponent>(this, "2");
	//runTimeComponents.Add(b);
	////runTimeComponents.Add(NewObject<URuntimeMeshComponent>(this, name));
	////runTimeComponents.Add(NewObject<URuntimeMeshComponent>(this, name));

	//for (URuntimeMeshComponent* runTimeComponent : runTimeComponents)
	//{
	//	if (runTimeComponent)	 //isnotvalid, bug
	//	{
	//		runTimeComponent->RegisterComponent();

	//		//runTimeComponent->SetWorldLocation(FVector(0.0,0.0,0.0));
	//		//runTimeComponent->SetWorldRotation(FRotator(0.0, 0.0, 0.0));
	//		runTimeComponent->SetWorldTransform(Transform);
	//		//RootComponent = runTimeComponent;
	//		//runTimeComponent->AttachTo(SceneComponent);//, FAttachmentTransformRules::KeepRelativeTransform);
	//		runTimeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);//GetRootComponent(), FName("Socket"), EAttachLocation::KeepWorldPosition);
	//	}
	//}

	Super::OnConstruction(Transform);

	NewChunksElements.SetNumUninitialized(0);
	FArr x;
	NewChunksElements.Add(x); NewChunksElements.Add(x); NewChunksElements.Add(x); NewChunksElements.Add(x); NewChunksElements.Add(x); NewChunksElements.Add(x);

	//FArr a, b, c, d, e, f;
	//NewChunksElements[0] = a;   NewChunksElements[1] = b; NewChunksElements[2] = c; NewChunksElements[3] = d; NewChunksElements[4] = e; NewChunksElements[5] = f;

	//GenerateChunk();
	//LoadChunk();

	//Load();
	//if (chunkFields.Num() != 0)
	//	UpdateMesh();

}


void AVoxelActor::GenerateChunk(TArray<int32>& arr)
{
	arr.SetNumUninitialized(chunkTotalElements);

	TArray <int32> noise = calculateNoise();

	int32 randomint01 = FMath::RandRange(0, 99);

	for (int32 x = 0; x < chunkLineElements.X; x++)
	{
		for (int32 y = 0; y < chunkLineElements.Y; y++)
		{
			for (int32 z = 0; z < chunkLineElements.Z; z++)
			{
				//GenerateBlock(FIntVector(x, y, z));

				int32 index = x + (y*chunkLineElements.X) + (z*chunkLineElements.X*chunkLineElements.Y);

				//if (ChunkCoordonates.Z <= 3)	 // = niveau de l'eau
				//	arr[index] = 2;
				//else
					arr[index] = 0;
				 
				//if (z + ChunkCoordonates.Z*chunkTotalElements <= 0)
				if (noise.Num() > (x + y * chunkLineElements.X))
				{

					if (z + ChunkCoordonates.Z*chunkLineElements.Z < 30 + noise[x + y * chunkLineElements.X] && z + ChunkCoordonates.Z*chunkLineElements.Z > 27 + noise[x + y * chunkLineElements.X])	//stone
					//if (z + ChunkCoordonates.Z*chunkLineElements.Z < 30 + SimplexNoise2D(x, y));
					{						
						arr[index] = 1;

					}
					else
					{
						if (z + ChunkCoordonates.Z*chunkLineElements.Z < 28 + noise[x + y * chunkLineElements.X])
						{
							int32 randomint11 = FMath::RandRange(0, 99);
							if (randomint11 <= 5)
							{
								if (randomint11 < 3)
									arr[index] = 11;
								if (randomint11 >= 3 && randomint11 < 5)
									arr[index] = 10;
								if (randomint11 == 5)
									arr[index] = 9;
							}
							else
								arr[index] = 8;

						}

						else
						{
							if (z + ChunkCoordonates.Z*chunkLineElements.Z == 30 + noise[x + y * chunkLineElements.X])	 //grass
							{
								//int32 randomint11 = FMath::RandRange(0, 99);
								//if (randomint11 < 5)
								//	chunkFields[index] = 5;
								//else
								arr[index] = 4;
							}
							else
							{
								if (z + ChunkCoordonates.Z*chunkLineElements.Z == 31 + noise[x + y * chunkLineElements.X])	 //grass
								{
									//int32 randomint11 = FMath::RandRange(0, 99);
									//if (randomint11 < 5)
									//	chunkFields[index] = 5;
									//else
									int32 randomint11 = FMath::RandRange(0, 99);
									if (randomint11 < 5)
										arr[index] = 100;
									else
									{
										int32 randomint11 = FMath::RandRange(0, 9999);
										if (randomint11 < 10)
											arr[index] = 101;
									}

								}
							}
						}
					}

				}
			}
		}
	}
}

void AVoxelActor::GenerateChunk2()
{
	chunkFields.SetNumZeroed(chunkTotalElements);
	//chunkFields.SetNumUninitialized(chunkTotalElements);
	//for (int i = 0; i < chunkTotalElements; i++)
	//{
	//	FblockProperties w;
	//	chunkFields.Add(w);
	//}

	TArray <int32> noise = calculateNoise();

	int32 randomint01 = FMath::RandRange(0, 99);

	for (int32 x = 0; x < chunkLineElements.X; x++)				  //TODO : finir par x			//z
	{
		for (int32 y = 0; y < chunkLineElements.Y; y++)										    //y
		{
			for (int32 z = 0; z < chunkLineElements.Z; z++)									    //x
			{

				int32 index = x + (y*chunkLineElements.X) + (z*chunkLineElements.X*chunkLineElements.Y);

				//chunkFields[index].location.X = x + ChunkCoordonates.X*chunkLineElements.X;
				//chunkFields[index].location.Y = y + ChunkCoordonates.Y*chunkLineElements.Y;
				//chunkFields[index].location.Z = z + ChunkCoordonates.Z*chunkLineElements.Z;

				FIntVector worldLocation = FIntVector(x + ChunkCoordonates.X*chunkLineElements.X, y + ChunkCoordonates.Y*chunkLineElements.Y, z + ChunkCoordonates.Z*chunkLineElements.Z);

				//chunkFields[index].W = GenerateBlocks(x + ChunkCoordonates.X*chunkLineElements.X, y + ChunkCoordonates.Y*chunkLineElements.Y, z + ChunkCoordonates.Z*chunkLineElements.Z,noise[x + y * chunkLineElements.X]); //ToDelete
				//chunkFields[index].blockType = GenerateBlocks(x + ChunkCoordonates.X*chunkLineElements.X, y + ChunkCoordonates.Y*chunkLineElements.Y, z + ChunkCoordonates.Z*chunkLineElements.Z, noise[x + y * chunkLineElements.X]); //ToDelete

				//GenerateBlock2(FIntVector(x, y, z), worldLocation, noise, chunkFields, index);
				referential->GenerateBlock_OneTime(FIntVector(x, y, z), worldLocation, noise, chunkFields, index);

			}
		}
	}
}



void AVoxelActor::GenerateBlock2(FIntVector relativeLocation, FIntVector worldLocation, TArray <int32>& noiseArray, TArray<FblockProperties>& chunk, int32 index)
{
	chunk[index].Objects.SetNumZeroed(1);
	int32& block = chunk[index].Objects[0].blockType;
	int32& x = worldLocation.X; int32& y = worldLocation.Y; int32& z = worldLocation.Z;
	int32& noise = noiseArray[relativeLocation.X + relativeLocation.Y * chunkLineElements.X];

	block = 0;
	//if (location.Z < 0)
	//	block = 1;

	if (z <= 30)	 // = niveau de l'eau
		block = 2;
	else
		block = 0;

	//if (z + ChunkCoordonates.Z*chunkTotalElements <= 0)
	if (noiseArray.Num() > (relativeLocation.X + relativeLocation.Y * chunkLineElements.X))
	{

		if (z < 30 + noise && z > 27 + noise)	//stone
																																															//if (z + ChunkCoordonates.Z*chunkLineElements.Z < 30 + SimplexNoise2D(x, y));
		{
			block = 1;

		}
		else
		{
			if (z < 28 + noise)
			{
				int32 randomint11 = FMath::RandRange(0, 99);
				if (randomint11 <= 5)
				{
					if (randomint11 < 3)
						block = 11;
					if (randomint11 >= 3 && randomint11 < 5)
						block = 10;
					if (randomint11 == 5)
						block = 9;
				}
				else
					block = 8;

			}

			else
			{
				if (z == 30 + noise)	 //grass
				{
					//int32 randomint11 = FMath::RandRange(0, 99);
					//if (randomint11 < 5)
					//	chunkFields[index] = 5;
					//else
					block = 4;
					if (x > 15000/2)
						block = 13;
					if (x < -15000/2)
						block = 14;
				}
				else
				{
					if (z == 31 + noise)	 //grass
					{
						FObjectProperties bigMesh;
						//int32 randomint11 = FMath::RandRange(0, 99);
						//if (randomint11 < 5)
						//	chunkFields[index] = 5;
						//else
						int32 randomint11 = FMath::RandRange(0, 99);
						if (randomint11 < 5)
						{
							//block = 100;
							bigMesh.blockType = 100;
							chunk[index].Objects.Add(bigMesh);
						}
						else
						{
							int32 randomint11 = FMath::RandRange(0, 9999);
							if (randomint11 < 10)
							{
								//block = 101;
								bigMesh.blockType = 100;
								chunk[index].Objects.Add(bigMesh);
							}
						}
						

					}
				}
			}
		}

		bool isStructured = false;
		int32 newID = GenerateStructs(worldLocation, isStructured, noise);
		if (isStructured)
			block = newID;
	}

	if (block == 0)
		chunk[index].Objects.RemoveAt(0);

}

void AVoxelActor::GenerateBlockByBP(FIntVector worldLocation, int32 noise, FblockProperties& returnedBlock)
{
	TArray<FblockProperties> blockArray; blockArray.SetNumZeroed(1); //blockArray.Add(block);
	TArray<int32> noiseArray; noiseArray.Add(noise);
	GenerateBlock2(FIntVector(0.0, 0.0, 0.0), worldLocation, noiseArray, blockArray, 0);

	returnedBlock = blockArray[0];
}

void AVoxelActor::UpdateMesh()
{
	TArray<FMeshSection> meshSections;
	meshSections.SetNum(Materials.Num());
	//int32 meshSectionsMax = 0;
	int32 el_num = 0;

	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, TEXT("Update Mesh"));

	for (UStaticMeshComponent* comp : Components)
		comp->DestroyComponent();
	Components.Empty();

	for (int32 x = 0; x < chunkLineElements.X; x++)
	{

		for (int32 y = 0; y < chunkLineElements.Y; y++)
		{


			for (int32 z = 0; z < chunkLineElements.Z; z++)
			{

				int32 index = x + (y*chunkLineElements.X) + (z*chunkLineElements.X*chunkLineElements.Y);

				//for (int iObject = 0; iObject < chunkFields[index].Objects.Num(); iObject++)
				for (FObjectProperties& bigMesh : chunkFields[index].Objects)	//FOR EACH OBJECT
				{

					//FObjectProperties& bigMesh = chunkFields[index].Objects[iObject];

					if (chunkFields.Num() > index)
					{
						int32 meshIndex = bigMesh.blockType;	//chunkFields[index].blockType;

						if (meshIndex > 0)
						{
							if (meshIndex < 100)
							{
								meshIndex--;
								if (meshSections.Num() > meshIndex && meshIndex >= 0)
								{
									TArray <FVector> &Vertices = meshSections[meshIndex].Vertices;	 //meshIndex
									TArray <int32> &Triangles = meshSections[meshIndex].Triangles;
									TArray <FVector> &Normals = meshSections[meshIndex].Normals;
									TArray<FVector2D> &UVs = meshSections[meshIndex].UVs;
									TArray<FRuntimeMeshTangent> &Tangents = meshSections[meshIndex].Tangents;
									TArray<FLinearColor> &VertexColors = meshSections[meshIndex].VertexColors;

									int32 elementID = meshSections[meshIndex].elementID;

									int32 type = 0;


									int triangle_num = 0;
									for (int i = 0; i < 6; i++)
									{
										int newIndex = index + bMask[i].X + (bMask[i].Y*chunkLineElements.X) + (bMask[i].Z*chunkLineElements.X*chunkLineElements.Y);

										bool flag = true;

										 
										if (meshIndex != 1)
										{

											//if (meshIndex >= 20) flag = true;
											/*else*/ if ((x + bMask[i].X < chunkLineElements.X) && (x + bMask[i].X >= 0) && (y + bMask[i].Y < chunkLineElements.Y) && (y + bMask[i].Y >= 0) && (z + bMask[i].Z < chunkLineElements.Y) && (z + bMask[i].Z >= 0)) // if is in chunk
											{
												if (newIndex < chunkFields.Num() && newIndex >= 0) // if is in chunk 
												{
													for (FObjectProperties& eachObject : chunkFields[newIndex].Objects)
													{																	  
														//if (eachObject.blockType < 1) flag = true; // TO CHANGE / WEB						  //if (chunkFields[newIndex].Objects[0].blockType < 1) flag = true;
														if (eachObject.blockType != 2 && eachObject.blockType != 16 && eachObject.blockType < 99 && eachObject.blockType > 0)	  //if (chunkFields[newIndex].Objects[0].blockType == 2 || chunkFields[newIndex].Objects[0].blockType > 99)
															flag = false;
													}
													//if (bMask[i].Z == 0)			// pour les pentes etc
													//{
													//	if (bMask[i].Y == 0)
													//		type = bMask[i].X + 2;

													//	if (bMask[i].X == 0)
													//		type = bMask[i].Y + 3;
													//}
												}
											}
											else
												flag = true;
										}
										else
										{
											if ((x + bMask[i].X < chunkLineElements.X) && (x + bMask[i].X >= 0) && (y + bMask[i].Y < chunkLineElements.Y) && (y + bMask[i].Y >= 0) && (z + bMask[i].Z < chunkLineElements.Y) && (z + bMask[i].Z >= 0)) // if is in chunk
											{
												if (newIndex < chunkFields.Num() && newIndex >= 0) // if is in chunk 
												{
													for (FObjectProperties& eachObject : chunkFields[newIndex].Objects)
													{
														//if (eachObject.blockType < 1) flag = true; // TO CHANGE / WEB
														if (eachObject.blockType == 2 || eachObject.blockType == 0) // || eachObject.blockType > 99)
															flag = false;
													}
												}
											}
											else
												flag = false;				//TODO : Check GlobalBlock 
											//else
											//{
											//	flag = true;

											//	FIntVector r = ChunkCoordonates + FIntVector(bMask[i]);

											//	//FVector k = FVector((x + bMask[i].X)*chunkLineElements.X*FvoxelSize.X, (y + bMask[i].Y)*chunkLineElements.Y*FvoxelSize.Y, (z + bMask[i].Z)*chunkLineElements.Z*FvoxelSize.Z);
											//	//FS_FloatAndIntVectors w = UChunks::GetChunk(FVector(chunkLineElements), FvoxelSize, k);
											//	//FIntVector v = UChunks::GetChunkLocalCubePosition(FVector(chunkLineElements), FvoxelSize, k);
											//	//TArray<int32> NewChunksElements;
											//	//FIntVector localCube = FIntVector(FGenericPlatformMath::Abs(fmod(x + bMask[i].X, chunkLineElements.X)), FGenericPlatformMath::Abs(fmod(y + bMask[i].Y, chunkLineElements.Y)), FGenericPlatformMath::Abs(fmod(z + bMask[i].Z, chunkLineElements.Z)));
											//	//Load(NewChunksElements, w.b);// FIntVector(fmod(x + bMask[i].X,chunkLineElements.X), fmod(y + bMask[i].Y, chunkLineElements.Y), fmod(z + bMask[i].Z, chunkLineElements.Z)));

											//	//TArray<int32> NewChunksElements;
											//	if (NewChunksElements[i].Arr.Num() == 0)
											//		Load(NewChunksElements[i].Arr, r);

											//	int32 newX, newY, newZ;
											//	if (x + bMask[i].X < 0)
											//		newX = x + bMask[i].X+chunkLineElements.X;
											//	if (x + bMask[i].X >= chunkLineElements.X)
											//		newX = x + bMask[i].X- chunkLineElements.X;

											//	if (y + bMask[i].Y < 0)
											//		newY = y + bMask[i].Y + chunkLineElements.Y;
											//	if (y + bMask[i].Y >= chunkLineElements.Y)
											//		newY = y + bMask[i].Y - chunkLineElements.Y;

											//	if (z + bMask[i].Z < 0)
											//		newZ = z + bMask[i].Z + chunkLineElements.Z;
											//	if (z + bMask[i].Z >= chunkLineElements.Z)
											//		newZ = z + bMask[i].Z - chunkLineElements.Z;

											//	int32 NewNewIndex = newX + (newY*chunkLineElements.X) + (newZ*chunkLineElements.X*chunkLineElements.Y);

											//	if (NewChunksElements.Num()>i)
											//		if (NewChunksElements[i].Arr.Num()>NewNewIndex && NewNewIndex > 0)
											//			if (NewChunksElements[i].Arr[NewNewIndex] == 2)
											//			{
											//			 flag = false;
											//			 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("FLAG FALSE"));
											//			}
											//}

										}

										//if (i == 2 || i == 4)
										//	flag = false;

										if (flag)
										{
											Triangles.Add(bTriangles[0] + triangle_num + elementID);
											Triangles.Add(bTriangles[1] + triangle_num + elementID);
											Triangles.Add(bTriangles[2] + triangle_num + elementID);
											Triangles.Add(bTriangles[3] + triangle_num + elementID);
											Triangles.Add(bTriangles[4] + triangle_num + elementID);
											Triangles.Add(bTriangles[5] + triangle_num + elementID);
											triangle_num += 4; // add a vertice to next triangle

											switch (i)
											{
											case 0: { // TODO : les -voxelSizeHalf au bon endroit
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals0));
												UVs.Add(FVector2D(float(x) * 2, float(y) * 2)); UVs.Add(FVector2D(float(x) * 2, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2));
												//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, UVs[0]));
												if (meshIndex == 1)
												{
													Triangles.Add(bTriangles[0] + triangle_num + elementID);
													Triangles.Add(bTriangles[1] + triangle_num + elementID);
													Triangles.Add(bTriangles[2] + triangle_num + elementID);
													Triangles.Add(bTriangles[3] + triangle_num + elementID);
													Triangles.Add(bTriangles[4] + triangle_num + elementID);
													Triangles.Add(bTriangles[5] + triangle_num + elementID);
													triangle_num += 4; // add a vertice to next triangle
													Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
													Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
													Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
													Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
													Normals.Append(bNormals0, ARRAY_COUNT(bNormals1));
													UVs.Add(FVector2D(float(x) * 2, float(y) * 2)); UVs.Add(FVector2D(float(x) * 2, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2));

													FLinearColor color = FLinearColor(255, 255, 255, i + 1);
													VertexColors.Add(color); VertexColors.Add(color); VertexColors.Add(color); VertexColors.Add(color);
												}
												break;
											}
											case 1: {
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals1));
												UVs.Add(FVector2D(float(x) * 2, float(y) * 2)); UVs.Add(FVector2D(float(x) * 2, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(y) * 2));
												break;
											}
											case 2: {
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals2));
												//UVs.Add(FVector2D(float(x), float(y))); UVs.Add(FVector2D(float(x), float(y) + 1.0)); UVs.Add(FVector2D(float(x) + 1.0, float(y) + 1.0)); UVs.Add(FVector2D(float(x) + 1.0, float(y)));
												UVs.Add(FVector2D(float(x) * 2, float(z) * 2)); UVs.Add(FVector2D(float(x) * 2, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(z) * 2));
												break;
											}
											case 3: {
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals3));
												UVs.Add(FVector2D(float(x) * 2, float(z) * 2)); UVs.Add(FVector2D(float(x) * 2, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(x) * 2 + 2.0, float(z) * 2));
												break;
											}
											case 4: {
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals4));
												UVs.Add(FVector2D(float(y) * 2, float(z) * 2)); UVs.Add(FVector2D(float(y) * 2, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(y) * 2 + 2.0, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(y) * 2 + 2.0, float(z) * 2));
												break;
											}
											case 5: {
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Vertices.Add(FVector(-FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), FvoxelSizeHalf.Z + (z*FvoxelSize.Z)));
												Normals.Append(bNormals0, ARRAY_COUNT(bNormals5));
												UVs.Add(FVector2D(float(y) * 2, float(z) * 2)); UVs.Add(FVector2D(float(y) * 2, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(y) * 2 + 2.0, float(z) * 2 + 2.0)); UVs.Add(FVector2D(float(y) * 2 + 2.0, float(z) * 2));
												break;
											}
											}

											//UVs.Append(bUVs, ARRAY_COUNT(bUVs));

											FLinearColor color = FLinearColor(255, 255, 255, i);
											VertexColors.Add(color); VertexColors.Add(color); VertexColors.Add(color); VertexColors.Add(color);


										}
									}
									el_num += triangle_num;
									meshSections[meshIndex].elementID += triangle_num;

									meshSections[meshIndex].meshIndex = meshIndex + 1;
								}
							}
							else
							{
								if (index >= chunkLineElements.X*chunkLineElements.Y)
								{
									////TODO : check range
									//if (chunkFields[index - chunkLineElements.X*chunkLineElements.Y].Objects[0].blockType == 0)
									//{
									//	//chunkFields[index].blockType = 0;
									//	bigMesh.blockType = 0;
									//}
									//else
									//{
										FMeshSection CustomMesh;
										CustomMeshes(FVector(+FvoxelSizeHalf.X + (x*FvoxelSize.X), -FvoxelSizeHalf.Y + (y*FvoxelSize.Y), -FvoxelSizeHalf.Z + (z*FvoxelSize.Z)), CustomMesh, meshIndex);
										//meshSections.Add(CustomMesh);
									//}
								}
								else
									//chunkFields[index].blockType = 0;
									bigMesh.blockType = 0;
							}
						}
					}


				}
			}
		}
	}

	//if (bInitialized)
	//	UpdateMeshTextures();

	//buildRuntimeMesh(runTimeComponent[0], meshSections)

	//if (true)// (UGameplayStatics::GetRealTimeSeconds(GetWorld()) < 10)
	//{
	//	runTimeComponent->ClearAllMeshSections();

	//	for (int i = 0; i < meshSections.Num(); i++)
	//	{
	//		if (meshSections[i].Vertices.Num() > 0)
	//		{
	//			buildRuntimeMesh(meshSections, i);

	//			if (meshSections[i].meshIndex != 2 && meshSections[i].meshIndex != 16)
	//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].UVs, meshSections[i].VertexColors, meshSections[i].Tangents, true, EUpdateFrequency::Frequent);
	//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
	//			{
	//				if (runTimeComponent->DoesSectionExist(i))
	//				{
	//					runTimeComponent->UpdateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors);
	//				}
	//				else
	//				{
	//					runTimeComponent->CreateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, true, false, false, false, EUpdateFrequency::Frequent);
	//				}
	//				//Compon(runTimeComponent, i, meshSections[i], true, EUpdateFrequency::Frequent);
	//				////runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals,
	//				////	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors,
	//				////	true/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
	//				////GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hellow!"));

	//			}
	//			else
	//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, 
	//				//	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, 
	//				//	false/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
	//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
	//				Compon(runTimeComponent, i, meshSections[i], false, EUpdateFrequency::Frequent);
	//		}
	//	}

	//	if (Materials.Num() > 0)
	//	{
	//		int s = 0;
	//		while (s < Materials.Num())
	//		{
	//			runTimeComponent->SetMaterial(s, Materials[s]);
	//			s++;
	//		}
	//	}
	//}

	buildRuntimeMesh(meshSections);
}

//void AVoxelActor::buildRuntimeMesh(TArray<FMeshSection>& meshSections, int32 i)
//{
//	URuntimeMeshComponent* runTimeComponent;
//	if (i == 1)
//		runTimeComponent = runTimeComponents[0];
//	else
//		runTimeComponent = runTimeComponents[1];
//
//	if (runTimeComponent->DoesSectionExist(i))
//	{
//		runTimeComponent->UpdateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors);
//	}
//	else
//	{
//		runTimeComponent->CreateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, true, false, false, false, EUpdateFrequency::Frequent);
//	}
//}

void AVoxelActor::buildRuntimeMesh(TArray<FMeshSection>& meshSections)
{
	//runTimeComponent->ClearAllMeshSections();
	
	for (URuntimeMeshComponent* runTimeComponent : runTimeComponents)
		runTimeComponent->ClearAllMeshSections();

	for (int i = 0; i < meshSections.Num(); i++)
	{
		if (meshSections[i].Vertices.Num() > 0)
		{
			URuntimeMeshComponent* runTimeComponent = SelectMeshRunTime(i);

			//if (meshSections[i].meshIndex != 2 && meshSections[i].meshIndex != 16)
			if (true)
				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].UVs, meshSections[i].VertexColors, meshSections[i].Tangents, true, EUpdateFrequency::Frequent);
				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
			{
				if (runTimeComponent->DoesSectionExist(i))
				{
					//runTimeComponent->ClearMeshSection(i);			   //TOLOOK
					runTimeComponent->UpdateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors);
				}
				else
				{
					runTimeComponent->CreateMeshSection_Blueprint(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, true, false, false, false, EUpdateFrequency::Frequent);
				}
				//runTimeComponent->SetMaterial(i, Materials[i]);
				//Compon(runTimeComponent, i, meshSections[i], true, EUpdateFrequency::Frequent);
				////runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals,
				////	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors,
				////	true/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
				////GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hellow!"));

			}
			else
				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, 
				//	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, 
				//	false/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
				Compon(runTimeComponent, i, meshSections[i], false, EUpdateFrequency::Frequent);
		}
	}

	if (Materials.Num() > 0)
	{
		int s = 0;
		while (s < Materials.Num())
		{
			URuntimeMeshComponent* runTimeComponent = SelectMeshRunTime(s);
			runTimeComponent->SetMaterial(s, Materials[s]);
			s++;
		}
	}


}

URuntimeMeshComponent* AVoxelActor::SelectMeshRunTime(int32 i)
{
	if (i == 1 || i == 15)
		return runTimeComponents[1];
	else
		return runTimeComponents[0];
}

//void AVoxelActor::UpdateMeshTextures()
//{
//	runTimeComponent->ClearAllMeshSections();
//
//	for (int i = 0; i < meshSections.Num(); i++)
//	{
//		if (meshSections[i].Vertices.Num() > 0)
//		{
//			if (meshSections[i].meshIndex != 2)
//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, meshSections[i].UVs, meshSections[i].VertexColors, meshSections[i].Tangents, true, EUpdateFrequency::Frequent);
//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
//			{
//				Compon(runTimeComponent, i, meshSections[i], true, EUpdateFrequency::Frequent);
//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals,
//				//	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors,
//				//	true/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
//				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Hellow!"));
//
//			}
//			else
//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, meshSections[i].Normals, 
//				//	meshSections[i].Tangents, meshSections[i].UVs, meshSections[i].UVs, meshSections[i].VertexColors, 
//				//	false/*colision*/, false, false, false, EUpdateFrequency::Frequent, false, true);
//				//runTimeComponent->CreateMeshSection(i, meshSections[i].Vertices, meshSections[i].Triangles, true, EUpdateFrequency::Frequent, ESectionUpdateFlags::None);
//				Compon(runTimeComponent, i, meshSections[i], false, EUpdateFrequency::Frequent);
//		}
//	}
//
//	if (Materials.Num() > 0)
//	{
//		int s = 0;
//		while (s < Materials.Num())
//		{
//			runTimeComponent->SetMaterial(s, Materials[s]);
//			s++;
//		}
//	}
//
//	meshSections.Empty();
//}

TArray<int32> AVoxelActor::calculateNoise()
{
	TArray<int32> noise;

	if (referential)
	{
		int32 chunkXvalue = referential->chunkLineElements.X*ChunkCoordonates.X;
		int32 chunkYvalue = referential->chunkLineElements.Y*ChunkCoordonates.Y;

		noise.Reserve(chunkLineElements.Y*chunkLineElements.X);	  //efficiency

		for (int y = 0; y < referential->chunkLineElements.Y; y++)
		{
			for (int x = 0; x < referential->chunkLineElements.X; x++)
			{
				noise.Add(referential->CalculateNoise_OneTime(FIntPoint(x + chunkXvalue, y + chunkYvalue)));
			}
		}

	}
	return noise;
}

int32 AVoxelActor::calculateNoise_OneTime_Implementation(FIntPoint location)
{
	return 0;
}

void AVoxelActor::Load_Implementation(TArray<FblockProperties>& arr, FIntVector ChunkCoordonates2)
{
	return;
}

void AVoxelActor::CustomMeshes_Implementation(FVector Location, FMeshSection& MeshSection, int32 meshIndex)
{
	return;
}

void AVoxelActor::Compon_Implementation(URuntimeMeshComponent* compo, int32 SectionIndex, FMeshSection Section, bool bCreateCollision, EUpdateFrequency UpdateFrequency)
{
	return;
}

int32 AVoxelActor::GenerateBlocks_Implementation(int32 x, int32 y, int32 z, int32 id)
{
	return 0;
}

int32 AVoxelActor::GenerateStructs_Implementation(FIntVector location, bool& isStruct, int32 noise)
{
	return 0;
}

//int32 AVoxelActor::GenerateStructs2(FIntVector location, bool& isStruct, int32 noise)
//{
//	FVector2D peak = GetMultiplePeaksInCorner2D(location, FVector2D(10.0,10.0));
//
//	FVector2D relativeLocation = FVector2D(abs(peak.X-location.X), abs(peak.Y - location.Y));
//
//	//int32 index = Get1DFrom3D();
//
//
//	return 0;
//}

void AVoxelActor::UpdateMeshBP_Implementation()
{
	return;
}

int32 AVoxelActor::getBlock(FblockProperties a)
{
	if (a.Objects.Num() > 0)
		return a.Objects[0].blockType;
	return 0;
}

void AVoxelActor::setVoxel(FVector localPos, int32 value)
{

	int32 x2 = localPos.X;
	int32 y2 = localPos.Y;
	int32 z2 = localPos.Z;

	int32 index = x2 + y2 * chunkLineElements.X + z2 * chunkLineElements.X*chunkLineElements.Y;

	if (chunkFields.Num() <= index)
		chunkFields.AddUninitialized(index - chunkFields.Num() + 1);

	//chunkFields[index].W = value;
	if (chunkFields[index].Objects.Num() == 0)
		chunkFields[index].Objects.AddUninitialized(1);

	if (index >= 0 && index < chunkFields.Num())
		if (chunkFields[index].Objects.Num() > 0 )
			chunkFields[index].Objects[0].blockType = value;

	if (value == 0)
		chunkFields[index].Objects.RemoveAt(0);

	UpdateMeshBP();
	UpdateMesh();
	//SaveChunk();
}

void AVoxelActor::setBlock(FIntVector localPos, int32 value, FObjectProperties& replacedValue, int32 objectIndex)
{
	int32 x2 = localPos.X;
	int32 y2 = localPos.Y;
	int32 z2 = localPos.Z;

	int32 index = x2 + y2 * chunkLineElements.X + z2 * chunkLineElements.X*chunkLineElements.Y;

	if (chunkFields.Num() <= index)
		chunkFields.AddUninitialized(index - chunkFields.Num() + 1);

	//chunkFields[index].W = value;
	if (chunkFields[index].Objects.Num() <= objectIndex)
	{
		chunkFields[index].Objects.AddUninitialized(objectIndex - chunkFields[index].Objects.Num() + 1);
		chunkFields[index].Objects[objectIndex].blockType = 0;
	}

	if (index >= 0 && index < chunkFields.Num())
		if (chunkFields[index].Objects.Num() > objectIndex)
		{
			replacedValue = chunkFields[index].Objects[objectIndex];
			chunkFields[index].Objects[objectIndex].blockType = value;
		}

	if (value == 0)
		chunkFields[index].Objects.RemoveAt(objectIndex);

	//UpdateMeshBP();
	//UpdateMesh();
}