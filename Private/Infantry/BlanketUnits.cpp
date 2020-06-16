// Fill out your copyright notice in the Description page of Project Settings.


#include "BlanketUnits.h"
#include "Perception/PawnSensingComponent.h"
#include "BlanketActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


ABlanketUnits::ABlanketUnits(){

    SenseComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

}

void ABlanketUnits::BeginPlay()
{
	Super::BeginPlay();
	
    //Setting up the pawn sensing comp so they detect only other units and buildings
    SenseComp->OnSeePawn.AddDynamic(this, &ABlanketUnits::OnPawnSeen);
    SenseComp->bOnlySensePlayers = false;
    SenseComp->bSeePawns = true;
}

//Currently a bare-bones function of teleporting the actor to the location
void ABlanketUnits::MoveUnit(FVector WhereToMove){

    SetActorLocation(WhereToMove, false);

}

//This function runs when the pawn sees another pawn
void ABlanketUnits::OnPawnSeen(APawn* SeenPawn){

    //UE_LOG(LogTemp, Warning, TEXT("Ref 016")); //Debug Line
    
    //Making sure the pawn is valid and not itself
    if(SeenPawn && SeenPawn != this){

        //Making sure the seen pawn is capable of having health
        ABlanketActor* ActorPawn = Cast<ABlanketActor>(SeenPawn);
    
        //And then attacking the pawn
        if (ActorPawn){

            //UE_LOG(LogTemp, Warning, TEXT("Ref 015")); //Debug Line

            Attack(ActorPawn);

        }
       

    }

}

//A function calculating the damage that a unit can do
/*Quick rundown:
The damage has an rng variance, so we calculate that first
Then we see if the damage is going to increase or decrease by this percent variance
And then when apply the damage change
*/
float ABlanketUnits::CalculateDamage(){

    float Variance = (float)rand()/RAND_MAX * DamageVariance; 
   // UE_LOG(LogTemp, Warning, TEXT("Variance: %f"), Variance); //Debug Line
    int32 IncreaseOrDeacrease = rand() % 2 + 1;
    //UE_LOG(LogTemp, Warning, TEXT("Int: %i"), IncreaseOrDeacrease); //Debug Line
    float DamageChange = 0.0f;
    if(IncreaseOrDeacrease == 1){

        DamageChange = BaseDamage * Variance; 

    } else {

        DamageChange = BaseDamage * Variance * -1.0f;

    }

    //UE_LOG(LogTemp, Warning, TEXT("DamageChange: %f"), DamageChange); //Debug Line

    return (BaseDamage + DamageChange);

}

//This should only be implemented inside the specific unit's code
void ABlanketUnits::Attack(ABlanketActor* HitActor){

    //UE_LOG(LogTemp, Error, TEXT("Error! No attack function is binded to a unit!"))

}