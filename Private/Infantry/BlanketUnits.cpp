// Fill out your copyright notice in the Description page of Project Settings.


#include "BlanketUnits.h"
#include "Perception/PawnSensingComponent.h"
#include "BlanketActor.h"


ABlanketUnits::ABlanketUnits(){

    SenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

    
    

}

void ABlanketUnits::BeginPlay()
{
	Super::BeginPlay();
	
    SenseComp->OnSeePawn.AddDynamic(this, &ABlanketUnits::OnPawnSeen);
    SenseComp->bOnlySensePlayers = false;
    SenseComp->bSeePawns = true;
}

void ABlanketUnits::MoveUnit(FVector WhereToMove){

    SetActorLocation(WhereToMove, false);

}

void ABlanketUnits::OnPawnSeen(APawn* SeenPawn){

     //UE_LOG(LogTemp, Warning, TEXT("Ref 016"));
    

     if(SeenPawn && SeenPawn != this){
        ABlanketActor* ActorPawn = Cast<ABlanketActor>(SeenPawn);
    
        if (ActorPawn){

            //UE_LOG(LogTemp, Warning, TEXT("Ref 015"));

            Attack(ActorPawn);

        }
       

    }

}

float ABlanketUnits::CalculateDamage(){

    float Variance = (float)rand()/RAND_MAX * DamageVariance;
   // UE_LOG(LogTemp, Warning, TEXT("Variance: %f"), Variance);
    int32 IncreaseOrDeacrease = rand() % 2 + 1;
    //UE_LOG(LogTemp, Warning, TEXT("Int: %i"), IncreaseOrDeacrease);
    float DamageChange = 0.0f;
    if(IncreaseOrDeacrease == 1){

        DamageChange = BaseDamage * Variance; 

    } else {

        DamageChange = BaseDamage * Variance * -1.0f;

    }

    //UE_LOG(LogTemp, Warning, TEXT("DamageChange: %f"), DamageChange);

    return (BaseDamage + DamageChange);

}

void ABlanketUnits::Attack(ABlanketActor* HitActor){

    //UE_LOG(LogTemp, Error, TEXT("Error! No attack function is binded to a unit!"))

}