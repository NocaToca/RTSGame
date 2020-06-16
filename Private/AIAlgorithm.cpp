// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAlgorithm.h"
#include "GameFrameWork/Actor.h"

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
void AIAlgorithm::Pathfind(AActor* Actor, FVector Destination){

    FVector StartLocation = Actor->GetActorLocation();

    float Distance = FVector::Dist(StartLocation, Destination);

    float IncrementalDistance = Distance/1000.0f;

    TArray<FVectorValues> VectorPath;
    FVectorValues StartingVector = FVectorValues(StartingVector, 0.0f, Distance, Distance, nullptr);
    VectorPath.Add(StartingVector);

    TArray<FVectorValues> AllVectors;
    AllVectors.Add(StartingVector);
  

    RayTrace(StartLocation, IncrementalDistance, VectorPath, Destination, AllVectors, Actor);

}

float AIAlgorithm::RayTrace(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor){

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
	QueryParams.AddIgnoredActor(MyOwner); 
	QueryParams.bTraceComplex = true; 

    if(GetWorld()->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){



    } else {

        float ForwardDistance = FVector::Dist(TraceEndForward, Destination);
        FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, StartingVector);

    }

    if(GetWorld()->LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){



    } else {

        float LeftDistance = FVector::Dist(TraceEndLeft, Destination);
        FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, StartingVector);

    }

    if(GetWorld()->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){



    } else {

        float BackDistance = FVector::Dist(TraceEndBehind, Destination);
        FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, StartingVector);

    }

    if(GetWorld()->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){



    } else {

        float RightDistance = FVector::Dist(TraceEndRight, Destination);
        FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, StartingVector);

    }

    do{

        

    } while (true);

    return VectorPath;

}

bool AIAlgorithm::RayTraceExtended(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, float PathWeight, float IncrementWeight){



}