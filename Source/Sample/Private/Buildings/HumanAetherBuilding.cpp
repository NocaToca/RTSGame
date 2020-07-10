// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanAetherBuilding.h"
#include "SamplePlayerController.h"

AHumanAetherBuilding::AHumanAetherBuilding(){

    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

void AHumanAetherBuilding::OnBuilt(ASamplePlayerController* MyOwner){

    OwningPlayer = MyOwner;

}

void AHumanAetherBuilding::Tick(float DeltaTime){

    Super::Tick(DeltaTime);

    if(OwningPlayer){

        OwningPlayer->Aether += ((AetherGeneration/10.0f) * DeltaTime);

    }

}