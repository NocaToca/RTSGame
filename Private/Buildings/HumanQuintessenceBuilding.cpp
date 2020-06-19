// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanQuintessenceBuilding.h"
#include "SamplePlayerController.h"
#include "Components/SkeletalMeshComponent.h"

AHumanQuintessenceBuilding::AHumanQuintessenceBuilding(){



}

void AHumanQuintessenceBuilding::OnBuilt(ASamplePlayerController* MyOwner){

    OwningPlayer = MyOwner;

}

void AHumanQuintessenceBuilding::Tick(float DeltaTime){

    Super::Tick(DeltaTime);

    if(OwningPlayer){

        OwningPlayer->Quintessence += ((QuintessenceGeneration / 1000.0f) * DeltaTime);
        UE_LOG(LogTemp, Log, TEXT("Quintessence: %f"), OwningPlayer->Quintessence);

    }

}