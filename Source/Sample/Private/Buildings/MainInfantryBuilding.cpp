// Fill out your copyright notice in the Description page of Project Settings.


#include "MainInfantryBuilding.h"


// Sets default values
AMainInfantryBuilding::AMainInfantryBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

}

// Called when the game starts or when spawned
void AMainInfantryBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainInfantryBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainInfantryBuilding::ClickedOn(){

	//Super::ClickedOn();

	UE_LOG(LogTemp, Log, TEXT("Yeet"));


}