// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanInfantryBuilding.h"
#include "SamplePlayerController.h"
#include "Infantry/HumanMarineUnit.h"

// Sets default values
AHumanInfantryBuilding::AHumanInfantryBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasHealthComp = true;

    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AHumanInfantryBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHumanInfantryBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHumanInfantryBuilding::ClickedOnBuilding(ASamplePlayerController* PlayerController){
    if(bClickedOn){

        return;

    }

	Super::ClickedOnBuilding(PlayerController);

    CurrentPlayerController = PlayerController;

	UE_LOG(LogTemp, Log, TEXT("Yeet"));

    bClickedOn = true;


}

void AHumanInfantryBuilding::CreateMarineUnit(){

    UE_LOG(LogTemp, Warning, TEXT("Ref014"));

    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    if(CurrentPlayerController){
        if(StarterMarineClass){

         GetWorld()->SpawnActor<AHumanMarineUnit>(StarterMarineClass, FVector(-477.0f, -385.0f, 423.0f), FRotator::ZeroRotator, SpawnParams);


        }

       

    }
    
}