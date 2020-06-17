// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAlgorithm.h"
#include "GameFrameWork/Actor.h"
#include "FVectorValues.h"
#include "DrawDebugHelpers.h"

AIAlgorithm::AIAlgorithm()
{
}

AIAlgorithm::~AIAlgorithm()
{
}
/*A* Pseudo-Code

First, since we have no nodes, we will create for ray-traces, one in the positive x and y
and one in the negative x and y, of a distance 1/1000th away from the node.

After we create each ending vector, we will see and store four things:

Its distance away from the destination
How many FVectors are before this one
The FVector that the FVector came from
Did the line trace hit something

And then we will also store the FVector in an array list

If the line trace hit something, we recalculate the 1/1000th away from the destination,
but re-create the weight of the node to the ratio of the first 1/1000th to the new
1/1000th (default rate is .001). This will keep happening as the line trace hits something

However, we will follow the closest FVector with the least amound of weight and we'll
do this by adding the distance and the weight of the vector and checking to see if there
are any other vectors closer. If there happens to be one with less weight, we use that until
either we reach the desination or another FVector has less weight.

Upon reaching the destination, we will take the FVector that got there with the least weight
and just back track from where that FVector came from until we get to the orginal FVector 
while adding those Vectors to an array before moving the character across that array*/
void AIAlgorithm::Pathfind(AActor* Actor, FVector Destination, UWorld* Worldz){

    FVector StartLocation = Actor->GetActorLocation();

    float Distance = FVector::Dist(StartLocation, Destination);

    float IncrementalDistance = Distance/10.0f;

    TArray<FVector> VectorPath;
    FVectorValues StartingVector(StartLocation, 0.0f, Distance, Distance, StartLocation);
    //VectorPath.Add(StartingVector);

    TArray<FVectorValues> AllVectors;
    //AllVectors.Add(StartingVector);
  

    float PathWeightMain = RayTrace(StartLocation, IncrementalDistance, VectorPath, Destination, AllVectors, Actor, Worldz);

    UE_LOG(LogTemp, Log, TEXT("PathWeight: %f"), PathWeightMain);

}

float AIAlgorithm::RayTrace(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, UWorld* Worldz){

    FRotator ForwardVector(0, 90, 0);
    FRotator LeftVector = FRotator(0, 180, 0);
    FRotator BehindVector(0, 270, 0);
    FRotator RightVector(0, 360, 0);

    UE_LOG(LogTemp, Log, TEXT("Increments: %f"), Increments);

    FVector TraceEndForward = StartingVector + (ForwardVector.Vector() * Increments);
    FVector TraceEndLeft = StartingVector + (LeftVector.Vector() * Increments);
    FVector TraceEndBehind = StartingVector + (BehindVector.Vector() * Increments);
    FVector TraceEndRight = StartingVector + (RightVector.Vector() * Increments);

    FHitResult HitForward;
    FHitResult HitLeft;
    FHitResult HitBehind;
    FHitResult HitRight;

    FCollisionQueryParams QueryParams; 
	QueryParams.AddIgnoredActor(MovingActor); 
	QueryParams.bTraceComplex = true; 



    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Front = FVectorValues(TraceEndForward, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Front);
        DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Blue, true, 10.0f, 10, 10.0f);
        UE_LOG(LogTemp, Warning, TEXT("Front Collided"));

    } else {

        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);
        AllVectors.Add(Front);
        UE_LOG(LogTemp, Log, TEXT("Foward Vector: %s"), *TraceEndForward.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
        
        FVectorValues Left = FVectorValues(TraceEndLeft, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Left);
        DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Blue, true, 10.0f, 10, 10.0f);
        UE_LOG(LogTemp, Warning, TEXT("Left Collided"));

    } else {

        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);
        AllVectors.Add(Left);
        UE_LOG(LogTemp, Log, TEXT("Left Vector: %s"), *TraceEndLeft.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Behind);
        DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Blue, true, 10.0f, 10, 10.0f);
        UE_LOG(LogTemp, Warning, TEXT("Behind Collided"));

    } else {

        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);
        AllVectors.Add(Behind);
        UE_LOG(LogTemp, Log, TEXT("Behind Vector: %s"), *TraceEndBehind.ToString());
        //FVector DebugBehind = FVector(TraceEndBehind.X, TraceEndBehind.Y, TraceEndBehind.Z + 50.0f);
        DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Right = FVectorValues(TraceEndRight, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Right);
        DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Blue, true, 10.0f, 10, 10.0f);
        UE_LOG(LogTemp, Warning, TEXT("Right Collided"));

    } else {

        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);
        AllVectors.Add(Right);

        UE_LOG(LogTemp, Log, TEXT("Right Vector: %s"), *TraceEndRight.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Red, true, 10.0f, 10, 10.0f);
    }






    float MinWeight = RAND_MAX;
    int32 IndexOfVector = 0;
    float MinPathWeight = RAND_MAX;
    int32 IndexOfMainPath = 0;
    float CheckFullPath = 0.0f;

    for(int32 i = 0; i < 4; i++){
        for(int32 k = 0; k < AllVectors.Num(); k++){

            if(AllVectors.Last(k).OverallWeight < MinWeight){

                MinWeight = AllVectors.Last(k).OverallWeight;
                IndexOfVector = k;

            }

        }

        if(IndexOfVector != 0){
            
            CheckFullPath = RayTraceExtended(AllVectors.Last(IndexOfVector).CurrentVector, Increments, VectorPath, Destination, AllVectors, MovingActor, AllVectors.Last(IndexOfVector).OverallWeight, AllVectors.Last(IndexOfVector).PathWeight, Worldz, 1.0f, StartingVector);

            if(CheckFullPath < MinPathWeight){

                IndexOfMainPath = i;
                MinPathWeight = CheckFullPath;
                DrawDebugLine(Worldz, AllVectors.Last(IndexOfVector).CurrentVector, StartingVector, FColor::Green, true, 10.0f, 15, 10.0f);

            }

            break;

        }

    }

    //VectorPathing(VectorPath, AllVectors, AllVectors.Last(AllVectors.Num()-1), Worldz, StartingVector);

    UE_LOG(LogTemp, Log, TEXT("AllVectors size: %i"), AllVectors.Num());

    return MinPathWeight;

}

float AIAlgorithm::RayTraceExtended(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, float PathWeight, float IncrementWeight, UWorld* Worldz, float NumberOfPaths, FVector MainStartingVector){

    UE_LOG(LogTemp, Warning, TEXT("Paths: %f"), NumberOfPaths);

    if(FVectorEstimate(StartingVector, Destination, NumberOfPaths)){

        //VectorPathing(VectorPath, AllVectors, AllVectors.Last(AllVectors.Num()-1), Worldz, MainStartingVector);
        return PathWeight;

    } else if(NumberOfPaths >= 100){

        //VectorPathing(VectorPath, AllVectors, AllVectors.Last(AllVectors.Num()-1), Worldz, MainStartingVector);
        return PathWeight;

    }

    FRotator ForwardVector(0, 90, 0);
    FRotator LeftVector = FRotator(0, 180, 0);
    FRotator BehindVector(0, 270, 0);
    FRotator RightVector(0, 360, 0);

    FVector TraceEndForward = StartingVector + (ForwardVector.Vector() * Increments);
    FVector TraceEndLeft = StartingVector + (LeftVector.Vector() * Increments);
    FVector TraceEndBehind = StartingVector + (BehindVector.Vector() * Increments);
    FVector TraceEndRight = StartingVector + (RightVector.Vector() * Increments);

    FHitResult HitForward;
    FHitResult HitLeft;
    FHitResult HitBehind;
    FHitResult HitRight;

    FCollisionQueryParams QueryParams; 
	QueryParams.AddIgnoredActor(MovingActor); 
	QueryParams.bTraceComplex = true; 


    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Front = FVectorValues(TraceEndForward, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Front);
        DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Blue, true, 10.0f, 10, 10.0f);

    } else {

        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);
        AllVectors.Add(Front);
        UE_LOG(LogTemp, Log, TEXT("Foward Vector: %s"), *TraceEndForward.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
        
        FVectorValues Left = FVectorValues(TraceEndLeft, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Left);
        DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Blue, true, 10.0f, 10, 10.0f);

    } else {

        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);
        AllVectors.Add(Left);
        UE_LOG(LogTemp, Log, TEXT("Left Vector: %s"), *TraceEndLeft.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Behind);
        DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Blue, true, 10.0f, 10, 10.0f);

    } else {

        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);
        AllVectors.Add(Behind);
        UE_LOG(LogTemp, Log, TEXT("Behind Vector: %s"), *TraceEndBehind.ToString());
        //FVector DebugBehind = FVector(TraceEndBehind.X, TraceEndBehind.Y, TraceEndBehind.Z + 50.0f);
        DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Red, true, 10.0f, 10, 10.0f);
    }



    if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){

        FVectorValues Right = FVectorValues(TraceEndRight, Increments, RAND_MAX, RAND_MAX, StartingVector);
        AllVectors.Add(Right);
        DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Blue, true, 10.0f, 10, 10.0f);

    } else {

        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);
        AllVectors.Add(Right);

        UE_LOG(LogTemp, Log, TEXT("Right Vector: %s"), *TraceEndRight.ToString());
        DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Red, true, 10.0f, 10, 10.0f);
    }




 
   

    float MinWeight = RAND_MAX;
    int32 IndexOfVector = 0;
    float MinPathWeight = RAND_MAX;
    int32 IndexOfMainPath = 0;
    float CheckFullPath = 0.0f;
    

    for(int32 i = 0; i < 4; i++){
        for(int32 k = 0; k < AllVectors.Num(); k++){

            if(AllVectors.Last(k).OverallWeight < MinWeight){

                MinWeight = AllVectors.Last(k).OverallWeight;
                IndexOfVector = k;

            }

        }

        if(IndexOfVector != 0){
            
            CheckFullPath = RayTraceExtended(AllVectors.Last(IndexOfVector).CurrentVector, Increments, VectorPath, Destination, AllVectors, MovingActor, AllVectors.Last(IndexOfVector).OverallWeight + PathWeight, AllVectors.Last(IndexOfVector).PathWeight, Worldz, NumberOfPaths + 1.0f, MainStartingVector);

            if(CheckFullPath < MinPathWeight){

                IndexOfMainPath = i;
                MinPathWeight = CheckFullPath;
                DrawDebugLine(Worldz, AllVectors.Last(IndexOfVector).CurrentVector, StartingVector, FColor::Green, true, 10.0f, 15, 10.0f);

            }

            break;

        }

    }

    

    return MinPathWeight;

}

bool AIAlgorithm::FVectorEstimate(FVector LocationOne, FVector LocationTwo, float Threshold){

    float LocOneX = LocationOne.X;
    float LocOneY = LocationOne.Y;
    float LocOneZ = LocationOne.Z;
    
    float LocTwoX = LocationTwo.X;
    float LocTwoY = LocationTwo.Y;
    float LocTwoZ = LocationTwo.Z;

    if(FMath::Abs(LocOneX - LocTwoX) <= Threshold){
        if(FMath::Abs(LocOneY - LocTwoY) <= Threshold){
            if(FMath::Abs(LocOneZ - LocTwoZ) <= Threshold){

                return true;

            }


        }


    }

    return false;

}

void AIAlgorithm::VectorPathing(TArray<FVector> VectorPath, TArray<FVectorValues> AllVectors, FVectorValues EndingVector, UWorld* Worldz, FVector StartingVector){

    

    FVector PreviousVector = EndingVector.PreviousVector;
    FVector LastVector = EndingVector.CurrentVector;
    DrawDebugLine(Worldz, LastVector, PreviousVector, FColor::Green, true, 10.0f, 15, 10.0f);
    VectorPath.Add(LastVector);
    int32 CrashPervention = 0;
    do{
    for(int32 i = 0; i < AllVectors.Num(); i++){

        if(AllVectors.Last(i).CurrentVector == PreviousVector){

            LastVector = AllVectors.Last(i).CurrentVector;
            PreviousVector = AllVectors.Last(i).PreviousVector;
            VectorPath.Add(LastVector);
            break;

        }

        CrashPervention++;

    } } while(StartingVector != PreviousVector || CrashPervention >= 10000);

    if(CrashPervention >= 10000){

        UE_LOG(LogTemp, Error, TEXT("Aborted VectorPathing() loop! Too many runs!"));

    } else if(CrashPervention <= 5){

        UE_LOG(LogTemp, Error, TEXT("Error! VectorPathing() loop didn't run!"));

    }

    for(int32 k = 1; k < VectorPath.Num(); k++){

        DrawDebugLine(Worldz, VectorPath.Last(k), VectorPath.Last(k-1), FColor::Green, true, 10.0f, 15, 10.0f);

    }

}