// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInfantryBuilding.h"
#include "SamplePlayerController.h"
#include "Infantry/HumanMarineUnit.h"

// Sets default values
AHumanInfantryBuilding::AHumanInfantryBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasHealthComp = true; //Buildings have health

    //Creating the mesh
    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AHumanInfantryBuilding::BeginPlay()
{
	Super::BeginPlay();

    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Setting it so the units always spawn
	
}

// Called every frame
void AHumanInfantryBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHumanInfantryBuilding::ClickedOnBuilding(ASamplePlayerController* PlayerController){

    //If it's already clicked on, theres literally no reason for use to run this function again
    if(bClickedOn){

        return;

    }

	Super::ClickedOnBuilding(PlayerController); 

    CurrentPlayerController = PlayerController; //Setting the player controller to the player controller passed in

	//UE_LOG(LogTemp, Log, TEXT("Yeet")); //Debug Line

    bClickedOn = true;


}

//Creating a Marine unit near the building
void AHumanInfantryBuilding::CreateMarineUnit(){

    //UE_LOG(LogTemp, Warning, TEXT("Ref014")); //Debug Line

    //Making sure that we have everything to need so the game doesn't crash before spawning the unit

    FVector SpawningLocation = GetActorLocation();

    SpawningLocation.X -= (BuildingX + 10.0f);

    if(CurrentPlayerController){
        if(StarterMarineClass){

         GetWorld()->SpawnActor<AHumanMarineUnit>(StarterMarineClass, SpawningLocation, FRotator::ZeroRotator, SpawnParams);

         


        }

       

    }

    //BuildUnit();
    
}

bool AHumanInfantryBuilding::BuildUnit(){

    

    return false;

}