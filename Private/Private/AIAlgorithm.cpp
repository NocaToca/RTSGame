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

    float IncrementalDistance = Distance/25.0f;

    TArray<FVector> VectorPath;
    FVectorValues StartingVector(StartLocation, 0.0f, Distance, Distance, true);
    //VectorPath.Add(StartingVector);

    TArray<FVectorValues> OpenVectors;
    OpenVectors.Add(StartingVector);

    TArray<FVectorValues> ClosedVectors;
  

    float PathWeightMain = RayTrace(StartLocation, IncrementalDistance, VectorPath, Destination, OpenVectors, Actor, Worldz, ClosedVectors, StartingVector);

    UE_LOG(LogTemp, Log, TEXT("PathWeight: %f"), PathWeightMain);

}


float AIAlgorithm::RayTrace(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> OpenVectors, AActor* MovingActor, UWorld* Worldz, TArray<FVectorValues> ClosedVectors, FVectorValues StartVectorValue){

    OpenVectors.Remove(StartVectorValue);
    ClosedVectors.Add(StartVectorValue);

    TArray<FVectorValues> Neighbors;

    FRotator RightVector(0, 90, 0);
    FRotator BehindVector = FRotator(0, 180, 0);
    FRotator LeftVector(0, 270, 0);
    FRotator ForwardVector(0, 360, 0);

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

    if(TraceEndForward != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
            float ForwardDistance = FVector::Dist(TraceEndForward, Destination)/100.0f;
            FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, true);
            ClosedVectors.Add(Front);
            DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Blue, true, 10.0f, 10, 10.0f);
        

        } else {

            float ForwardDistance = FVector::Dist(TraceEndForward, Destination)/100.0f;
            FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, false);
            //OpenVectors.Add(Front);
            UE_LOG(LogTemp, Log, TEXT("Foward Vector: %s"), *TraceEndForward.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Red, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Front);
        }

    }
    


    if(TraceEndLeft != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
            float LeftDistance = FVector::Dist(TraceEndLeft, Destination)/100.0f;
            FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, true);
            ClosedVectors.Add(Left);
            DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float LeftDistance = FVector::Dist(TraceEndLeft, Destination)/100.0f;
            FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, false);
            //OpenVectors.Add(Left);
            UE_LOG(LogTemp, Log, TEXT("Left Vector: %s"), *TraceEndLeft.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Yellow, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Left);
        }

    }
    


    if(TraceEndBehind != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitBehind, StartingVector, TraceEndBehind, ECC_Visibility, QueryParams)){
            float BackDistance = FVector::Dist(TraceEndBehind, Destination)/100.0f;
            FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, true);
            ClosedVectors.Add(Behind);
            DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float BackDistance = FVector::Dist(TraceEndBehind, Destination)/100.0f;
            FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, false);
            //OpenVectors.Add(Behind);
            UE_LOG(LogTemp, Log, TEXT("Behind Vector: %s"), *TraceEndBehind.ToString());
            //FVector DebugBehind = FVector(TraceEndBehind.X, TraceEndBehind.Y, TraceEndBehind.Z + 50.0f);
            DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Magenta, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Behind);
        }

    }
    


    if(TraceEndRight != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitRight, StartingVector, TraceEndRight, ECC_Visibility, QueryParams)){
            float RightDistance = FVector::Dist(TraceEndRight, Destination)/100.0f;
            FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, true);
            ClosedVectors.Add(Right);
            DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float RightDistance = FVector::Dist(TraceEndRight, Destination)/100.0f;
            FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, false);
            //OpenVectors.Add(Right);
            UE_LOG(LogTemp, Log, TEXT("Right Vector: %s"), *TraceEndRight.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Cyan, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Right);
        }

    }

    for(int32 i = 0; i <Neighbors.Num(); i++){

        FVectorValues CurrentVectorValue = Neighbors.Last(i);

        if(!ClosedVectors.Contains(CurrentVectorValue) && !CurrentVectorValue.bDidCollide){

            int32 TempPathWeight = StartVectorValue.PathWeight + 1.0f;

            if(OpenVectors.Contains(CurrentVectorValue)){
                if(TempPathWeight < CurrentVectorValue.PathWeight){

                    CurrentVectorValue.PathWeight = TempPathWeight;

                }


            } else {

                CurrentVectorValue.PathWeight = TempPathWeight;
                OpenVectors.Add(CurrentVectorValue);

            }

            CurrentVectorValue.Distance = FVector::Dist(CurrentVectorValue.CurrentVector, Destination);
            CurrentVectorValue.OverallWeight = CurrentVectorValue.Distance + CurrentVectorValue.PathWeight;

            //CurrentVectorValue.PreviousVector = StartVectorValue;

        }

    }



    float MinWeight = RAND_MAX;
    int32 IndexOfVector = 0;
    float MinPathWeight = RAND_MAX;
    int32 IndexOfMainPath = 0;
    float CheckFullPath = 0.0f;

    UE_LOG(LogTemp, Warning, TEXT("First Vector: %s"), *OpenVectors.Last(0).CurrentVector.ToString());

    
        for(int32 k = 0; k < OpenVectors.Num(); k++){

            if(OpenVectors.Last(k).OverallWeight < OpenVectors.Last(IndexOfVector).OverallWeight){

                UE_LOG(LogTemp, Log, TEXT("OpenVectors size: %i"), OpenVectors.Num());
                UE_LOG(LogTemp, Warning, TEXT("Chosen Vector: %s"), *OpenVectors.Last(k).CurrentVector.ToString());
                

                MinWeight = OpenVectors.Last(k).OverallWeight;
                IndexOfVector = k;
                
                
                

            }

        }

        if(IndexOfVector != -1){
            
            CheckFullPath = RayTraceExtended(OpenVectors.Last(IndexOfVector).CurrentVector, Increments, VectorPath, Destination, OpenVectors, MovingActor, OpenVectors.Last(IndexOfVector).OverallWeight, OpenVectors.Last(IndexOfVector).PathWeight, Worldz, 1.0f, StartingVector, StartingVector, ClosedVectors, OpenVectors.Last(IndexOfVector));

            if(CheckFullPath < OpenVectors.Last(IndexOfVector).OverallWeight){

               
                MinPathWeight = CheckFullPath;
                DrawDebugLine(Worldz, OpenVectors.Last(IndexOfVector).CurrentVector, StartingVector, FColor::Green, true, 10.0f, 15, 10.0f);

            }

           

        }

    

    //VectorPathing(VectorPath, OpenVectors, OpenVectors.Last(OpenVectors.Num()-1), Worldz, StartingVector);

    UE_LOG(LogTemp, Log, TEXT("OpenVectors size: %i"), OpenVectors.Num());

    return MinPathWeight;

}

float AIAlgorithm::RayTraceExtended(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> OpenVectors, AActor* MovingActor, float PathWeight, float IncrementWeight, UWorld* Worldz, float NumberOfPaths, FVector MainStartingVector, FVector PreviousVector, TArray<FVectorValues> ClosedVectors, FVectorValues StartVectorValue){

    UE_LOG(LogTemp, Warning, TEXT("Paths: %f"), NumberOfPaths);

    TArray<FVectorValues> Neighbors;

    if(FVectorEstimate(StartingVector, Destination, 10.0f)){

        //VectorPathing(VectorPath, OpenVectors, OpenVectors.Last(OpenVectors.Num()-1), Worldz, MainStartingVector);
        return PathWeight;

    } else if(NumberOfPaths >= 1000){

        DrawDebugLine(Worldz, StartingVector, MainStartingVector, FColor::Orange, true, 10.0f, 15, 5.0f);
        //VectorPathing(VectorPath, OpenVectors, OpenVectors.Last(OpenVectors.Num()-1), Worldz, MainStartingVector);
        return PathWeight;

    }

    OpenVectors.Remove(StartVectorValue);
    ClosedVectors.Add(StartVectorValue);

    FRotator RightVector(0, 90, 0);
    FRotator BehindVector = FRotator(0, 180, 0);
    FRotator LeftVector(0, 270, 0);
    FRotator ForwardVector(0, 360, 0);

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



    if(TraceEndForward != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitForward, StartingVector, TraceEndForward, ECC_Visibility, QueryParams)){
            float ForwardDistance = FVector::Dist(TraceEndForward, Destination)/100.0f;
            FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, true);
            ClosedVectors.Add(Front);
            DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Blue, true, 10.0f, 10, 10.0f);
        

        } else {

            float ForwardDistance = FVector::Dist(TraceEndForward, Destination)/100.0f;
            FVectorValues Front = FVectorValues(TraceEndForward, Increments, ForwardDistance, Increments + ForwardDistance, false);
            //OpenVectors.Add(Front);
            UE_LOG(LogTemp, Log, TEXT("Foward Vector: %s"), *TraceEndForward.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndForward, FColor::Red, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Front);
        }

    }
    


    if(TraceEndLeft != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitLeft, StartingVector, TraceEndLeft, ECC_Visibility, QueryParams)){
            float LeftDistance = FVector::Dist(TraceEndLeft, Destination)/100.0f;
            FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, true);
            ClosedVectors.Add(Left);
            DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float LeftDistance = FVector::Dist(TraceEndLeft, Destination)/100.0f;
            FVectorValues Left = FVectorValues(TraceEndLeft, Increments, LeftDistance, Increments + LeftDistance, false);
            //OpenVectors.Add(Left);
            UE_LOG(LogTemp, Log, TEXT("Left Vector: %s"), *TraceEndLeft.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndLeft, FColor::Yellow, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Left);
        }

    }
    


    if(TraceEndBehind != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitBehind, StartingVector, TraceEndBehind, ECC_Visibility, QueryParams)){
            float BackDistance = FVector::Dist(TraceEndBehind, Destination)/100.0f;
            FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, true);
            ClosedVectors.Add(Behind);
            DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float BackDistance = FVector::Dist(TraceEndBehind, Destination)/100.0f;
            FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, BackDistance, Increments + BackDistance, false);
            //OpenVectors.Add(Behind);
            UE_LOG(LogTemp, Log, TEXT("Behind Vector: %s"), *TraceEndBehind.ToString());
            //FVector DebugBehind = FVector(TraceEndBehind.X, TraceEndBehind.Y, TraceEndBehind.Z + 50.0f);
            DrawDebugLine(Worldz, StartingVector, TraceEndBehind, FColor::Magenta, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Behind);
        }

    }
    


    if(TraceEndRight != StartingVector){

        if(Worldz->LineTraceSingleByChannel(HitRight, StartingVector, TraceEndRight, ECC_Visibility, QueryParams)){
            float RightDistance = FVector::Dist(TraceEndRight, Destination)/100.0f;
            FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, true);
            ClosedVectors.Add(Right);
            DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Blue, true, 10.0f, 10, 10.0f);

        } else {

            float RightDistance = FVector::Dist(TraceEndRight, Destination)/100.0f;
            FVectorValues Right = FVectorValues(TraceEndRight, Increments, RightDistance, Increments + RightDistance, false);
            //OpenVectors.Add(Right);
            UE_LOG(LogTemp, Log, TEXT("Right Vector: %s"), *TraceEndRight.ToString());
            DrawDebugLine(Worldz, StartingVector, TraceEndRight, FColor::Cyan, true, 10.0f, 10, 10.0f);
            Neighbors.Add(Right);
        }

    }
    
    for(int32 i = 0; i <Neighbors.Num(); i++){

        FVectorValues CurrentVectorValue = Neighbors.Last(i);

        if(!ClosedVectors.Contains(CurrentVectorValue) && !CurrentVectorValue.bDidCollide){

            int32 TempPathWeight = StartVectorValue.PathWeight + 1.0f;

            if(OpenVectors.Contains(CurrentVectorValue)){
                if(TempPathWeight < CurrentVectorValue.PathWeight){

                    CurrentVectorValue.PathWeight = TempPathWeight;

                }


            } else {

                CurrentVectorValue.PathWeight = TempPathWeight;
                OpenVectors.Add(CurrentVectorValue);

            }

            CurrentVectorValue.Distance = FVector::Dist(CurrentVectorValue.CurrentVector, Destination);
            CurrentVectorValue.OverallWeight = CurrentVectorValue.Distance + CurrentVectorValue.PathWeight;

            //CurrentVectorValue.PreviousVector = StartVectorValue;

        }

    }



 
   

    float MinWeight = RAND_MAX;
    int32 IndexOfVector = 0;
    float MinPathWeight = RAND_MAX;
    int32 IndexOfMainPath = 0;
    float CheckFullPath = 0.0f;
    bool bIsPreviousVector = false;
    

    
        for(int32 k = 0; k < OpenVectors.Num(); k++){

            if(OpenVectors.Last(k).OverallWeight < OpenVectors.Last(IndexOfVector).OverallWeight){

                IndexOfVector = k;

            }

        }

        if(IndexOfVector != -1){
            
            VectorPath.Add(OpenVectors.Last(IndexOfVector).CurrentVector);
            
                CheckFullPath = RayTraceExtended(OpenVectors.Last(IndexOfVector).CurrentVector, Increments, VectorPath, Destination, OpenVectors, MovingActor, OpenVectors.Last(IndexOfVector).OverallWeight + PathWeight, OpenVectors.Last(IndexOfVector).PathWeight, Worldz, NumberOfPaths + 1.0f, MainStartingVector, StartingVector, ClosedVectors, OpenVectors.Last(IndexOfVector));


            

            
            if(CheckFullPath < OpenVectors.Last(IndexOfVector).OverallWeight){

                
                MinPathWeight = CheckFullPath;
                DrawDebugLine(Worldz, OpenVectors.Last(IndexOfVector).CurrentVector, StartingVector, FColor::Green, true, 10.0f, 15, 10.0f);
                

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

void AIAlgorithm::VectorPathing(TArray<FVector> VectorPath, TArray<FVectorValues> OpenVectors, FVectorValues EndingVector, UWorld* Worldz, FVector StartingVector){

    

    // //FVector PreviousVector = EndingVector.PreviousVector;
    // FVector LastVector = EndingVector.CurrentVector;
    // DrawDebugLine(Worldz, LastVector, PreviousVector, FColor::Green, true, 10.0f, 15, 10.0f);
    // VectorPath.Add(LastVector);
    // int32 CrashPervention = 0;
    // do{
    // for(int32 i = 0; i < OpenVectors.Num(); i++){

    //     if(OpenVectors.Last(i).CurrentVector == PreviousVector){

    //         LastVector = OpenVectors.Last(i).CurrentVector;
    //         //PreviousVector = OpenVectors.Last(i).PreviousVector;
    //         VectorPath.Add(LastVector);
    //         break;

    //     }

    //     CrashPervention++;

    // } } while(StartingVector != PreviousVector || CrashPervention >= 10000);

    // if(CrashPervention >= 10000){

    //     UE_LOG(LogTemp, Error, TEXT("Aborted VectorPathing() loop! Too many runs!"));

    // } else if(CrashPervention <= 5){

    //     UE_LOG(LogTemp, Error, TEXT("Error! VectorPathing() loop didn't run!"));

    // }

    // for(int32 k = 1; k < VectorPath.Num(); k++){

    //     DrawDebugLine(Worldz, VectorPath.Last(k), VectorPath.Last(k-1), FColor::Green, true, 10.0f, 15, 10.0f);

    // }

}

FRotator AIAlgorithm::Find2DDirection(FVector FirstVector, FVector PreviousVector){

    float LocOneX = FirstVector.X;
    float LocOneY = FirstVector.Y;
    
    float LocTwoX = PreviousVector.X;
    float LocTwoY = PreviousVector.Y;
 
    if(LocOneX - LocTwoX == 0){
        if(LocOneY - LocTwoY > 0){
            return FRotator(0, 90, 0);

        } else {
            return FRotator(0, 270, 0);

        }


    }

    if(LocTwoY - LocOneY == 0){
        if(LocOneX - LocTwoX > 0){
            return FRotator(0, 360, 0);

        } else {
            return FRotator(0, 180, 0);

        }


    }
    return FRotator::ZeroRotator;

}

FVector AIAlgorithm::FindLastVectorInDirection(FRotator Direction, TArray<FVector> VectorPath, float Increments){

    FVector RotationVector = Direction.Vector();

    for(int32 i = 1; i < VectorPath.Num(); i++){

        FVector CheckVector = VectorPath.Last(i-1) + (RotationVector * Increments);
        if(CheckVector != VectorPath.Last(i)){

            return CheckVector;

        }

    }

    return VectorPath.Last(0);

}