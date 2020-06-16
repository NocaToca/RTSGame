// Fill out your copyright notice in the Description page of Project Settings.


#include "BlanketActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "SamplePlayerController.h"
#include "BlanketBuildings.h"
#include "BlanketUnits.h"

// Sets default values
ABlanketActor::ABlanketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	

}

// Called when the game starts or when spawned
void ABlanketActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlanketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ABlanketActor::ObjectType(ABlanketActor* Object){

	UE_LOG(LogTemp, Warning, TEXT("Ref011"));
	ABlanketUnits* Unit = Cast<ABlanketUnits>(Object);
	if(Unit){

		return 1;

	}

	UE_LOG(LogTemp, Warning, TEXT("Ref010"));
	ABlanketBuildings* Building = Cast<ABlanketBuildings>(Object);
	if(Object){

		return 0;

	}

	return -1;
}

