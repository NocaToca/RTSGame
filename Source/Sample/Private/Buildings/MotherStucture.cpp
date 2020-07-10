// Fill out your copyright notice in the Description page of Project Settings.


#include "MotherStucture.h"
#include "Components/SkeletalMeshComponent.h"

AMotherStucture::AMotherStucture(){

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;


}

bool AMotherStucture::InRange(FVector Vector){

    FVector AssessingActorLocation = Vector;
    FVector ThisLocation = GetActorLocation();

    float x = ThisLocation.X - AssessingActorLocation.X;
    float y = ThisLocation.Y - AssessingActorLocation.Y;

    float r = FMath::Sqrt((y*y) + (x*x));

    if(r <= BuildingRadius){

        return true;

    }

    return false;

}