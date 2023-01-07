// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Components/WidgetComponent.h"
//#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Entities.generated.h"

UCLASS()
class RPG_API AEntities : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntities();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = HUD)
	//	class UWidgetComponent* Widget;
	//

	//// The class that will be used for the Items Nameplate
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	//	TSubclassOf<class UUserWidget> NameplateUIClass;

	// The instance of the players Inventory UI Widget
	//UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = UI)
	//	UUserWidget* NameplateWidget;

};
