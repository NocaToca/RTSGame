// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAlgorithm.h"
#include "GameFrameWork/Actor.h"
#include "FVectorValues.h"

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
void AIAlgorithm::Pathfind(AActor* Actor, FVector Destination, UWorld Worldz){

    FVector StartLocation = Actor->GetActorLocation();

    float Distance = FVector::Dist(StartLocation, Destination);

    float IncrementalDistance = Distance/100.0f;

    TArray<FVectorValues> VectorPath;
    FVectorValues StartingVector(StartLocation, 0.0f, Distance, Distance, StartLocation);
    VectorPath.Add(StartingVector);

    TArray<FVectorValues> AllVectors;
    AllVectors.Add(StartingVector);
  

    float PathWeightMain = RayTrace(StartLocation, IncrementalDistance, VectorPath, Destination, AllVectors, Actor, Worldz);

    UE_LOG(LogTemp, Log, TEXT("PathWeight: %f"), PathWeightMain);

}

float AIAlgorithm::RayTrace(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, UWorld Worldz){

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

    FVectorValues Front;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);


    } else {

        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);

    }

    FVectorValues Left;

    if(Worldz.LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);


    } else {

        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);

    }

    FVectorValues Behind;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);


    } else {

        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);

    }

    FVectorValues Right;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);


    } else {

        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);

    }

    AllVectors.Add(Front);
    AllVectors.Add(Left);
    AllVectors.Add(Behind);
    AllVectors.Add(Right);

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
            
            CheckFullPath = RayTraceExtended(AllVectors.Last(IndexOfVector).CurrentVector, 1.0f, VectorPath, Destination, AllVectors, MovingActor, AllVectors.Last(IndexOfVector).OverallWeight, AllVectors.Last(IndexOfVector).PathWeight, Worldz);

            if(CheckFullPath < MinPathWeight){

                IndexOfMainPath = i;
                MinPathWeight = CheckFullPath;

            }

        }

    }

    return MinPathWeight;

}

float AIAlgorithm::RayTraceExtended(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, float PathWeight, float IncrementWeight, UWorld Worldz){

    if(StartingVector == Destination){

        return PathWeight;

    } else if(Increments >= 500){

        return PathWeight * 1000000.0f;

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

    FVectorValues Front;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);


    } else {

        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);

    }

    FVectorValues Left;

    if(Worldz.LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);


    } else {

        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);

    }

    FVectorValues Behind;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);


    } else {

        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);

    }

    FVectorValues Right;

    if(Worldz.LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);


    } else {

        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);

    }

    AllVectors.Add(Front);
    AllVectors.Add(Left);
    AllVectors.Add(Behind);
    AllVectors.Add(Right);

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
            
            CheckFullPath = RayTraceExtended(AllVectors.Last(IndexOfVector).CurrentVector, Increments + 1.0f, VectorPath, Destination, AllVectors, MovingActor, AllVectors.Last(IndexOfVector).OverallWeight + PathWeight, AllVectors.Last(IndexOfVector).PathWeight, World);

            if(CheckFullPath < MinPathWeight){

                IndexOfMainPath = i;
                MinPathWeight = CheckFullPath;

            }

        }

    }

    return MinPathWeight;

}