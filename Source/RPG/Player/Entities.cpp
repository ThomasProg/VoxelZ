// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities.h"


// Sets default values
AEntities::AEntities()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget1"));*/

	//if (NameplateUIClass)
	//{
	//	if (!NameplateWidget)
	//	{
	//		NameplateWidget = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), NameplateUIClass);
	//		if (!NameplateWidget)
	//		{
	//			return;
	//		}

	//		NameplateWidget->AddToViewport();
	//		NameplateWidget->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//}
}

// Called when the game starts or when spawned
void AEntities::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntities::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntities::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

