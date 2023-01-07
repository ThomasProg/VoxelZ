// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector APlayerCharacter::GetCubeRelativeLocation(FVector Start, FVector Vec)
{
	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, Start + FVector(0.0, 0.0, -5.0), Start + FVector(0.0, 0.0, 10.0), ECC_Visibility))
	{
		if (Vec.Z > 0.0)
			return FVector(0.0, 0.0, 1.0);
		else
			return FVector(0.0, 0.0, -1.0);
	}
	else
	{
		if (GetWorld()->LineTraceSingleByChannel(hit, Start + FVector(0.0, -5.0, 0.0), Start + FVector(0.0, 10.0, 0.0), ECC_Visibility))
		{
			if (Vec.Y > 0.0)
				return FVector(0.0, 1.0, 0.0);
			else
				return FVector(0.0, -1.0, 0.0);
		}
		else
		{
			if (GetWorld()->LineTraceSingleByChannel(hit, Start + FVector(-5.0, 0.0, 0.0), Start + FVector(10.0, 0.0, 0.0), ECC_Visibility))
			{
				if (Vec.X > 0.0)
					return FVector(1.0, 0.0, 0.0);
				else
					return FVector(-1.0, 0.0, 0.0);
			}
			else
				return FVector(0.0, 0.0, 0.0);
		}
	}
}