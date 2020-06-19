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
and one in the negative x and y, of a h 1/1000th away from the node.
After we create each ending vector, we will see and store four things:
Its h away from the destination
How many FVectors are before this one
The FVector that the FVector came from
Did the line trace hit something
And then we will also store the FVector in an array list
If the line trace hit something, we recalculate the 1/1000th away from the destination,
but re-create the weight of the node to the ratio of the first 1/1000th to the new
1/1000th (default rate is .001). This will keep happening as the line trace hits something
However, we will follow the closest FVector with the least amound of weight and we'll
do this by adding the h and the weight of the vector and checking to see if there
are any other vectors closer. If there happens to be one with less weight, we use that until
either we reach the desination or another FVector has less weight.
Upon reaching the destination, we will take the FVector that got there with the least weight
and just back track from where that FVector came from until we get to the orginal FVector 
while adding those Vectors to an array before moving the character across that array*/
void AIAlgorithm::Pathfind(AActor* Actor, FVector Destination, UWorld* Worldz){

    FVector StartLocation = Actor->GetActorLocation();

    float Distance = FVector::Dist(StartLocation, Destination);

    float Increments = Distance/10.0f;

    TArray<FVectorValues> AllVectors;

    TArray<FVector> VectorPath;
    FVectorValues StartVectorValues(StartLocation, 0.0f, Distance, Distance, true);
    //VectorPath.Add(CurrentVector.CurrentVector);

    TArray<FVectorValues> OpenVectors;
    OpenVectors.Add(StartVectorValues);

    TArray<FVectorValues> ClosedVectors;

    int32 CrashPrevention = 0;

    while(OpenVectors.Num() != 0){
        
        int32 LowestIndex = 0;
        UE_LOG(LogTemp, Warning, TEXT("%i"), OpenVectors.Num());
        for(int32 i = 0; i < OpenVectors.Num(); i++){

            if(OpenVectors.Last(i).f < OpenVectors.Last(LowestIndex).f){
                
                LowestIndex = i;

            }
            

        }

        FVectorValues CurrentVector = OpenVectors.Last(LowestIndex);

        UE_LOG(LogTemp, Log, TEXT("g value: %f"), CurrentVector.g);
        UE_LOG(LogTemp, Log, TEXT("h value: %f"), CurrentVector.h);
        UE_LOG(LogTemp, Log, TEXT("f value: %f"), CurrentVector.f);

        FCollisionQueryParams QueryParams; 
        QueryParams.AddIgnoredActor(Actor); 
        QueryParams.bTraceComplex = true; 

        FHitResult TestObstacles;

        if(FVectorEstimate(CurrentVector.CurrentVector, Destination, Increments/2.0f)){

            UE_LOG(LogTemp, Log, TEXT("Path Found"));
            UE_LOG(LogTemp, Log, TEXT("CrashPrevention: %i"), CrashPrevention);
            break;

        } else if(CrashPrevention >= 5000){

            UE_LOG(LogTemp, Error, TEXT("CrashPrevention Ran"));
            DrawDebugLine(Worldz, CurrentVector.CurrentVector, Destination, FColor::Orange, true, 10.0f, 15, 10.0f);
            break;

        } else if(!Worldz->LineTraceSingleByChannel(TestObstacles, CurrentVector.CurrentVector, Destination, ECC_Visibility, QueryParams)){
            FVectorValues Temp = CurrentVector;


            int32 Check = 0;
            VectorPath.Add(Temp.CurrentVector);
            while(Temp.bHasPrevious && Check < 2){

                    
                Check++;

            }
            if(Check == 2){

                UE_LOG(LogTemp, Error, TEXT("Check Died"));

            }

            for(int32 i = 1; i < VectorPath.Num(); i++){

                DrawDebugLine(Worldz, VectorPath.Last(i), VectorPath.Last(i-1), FColor::Green, true, 10.0f, 20, 10.0f);

            }
            for(int32 i = 0; i < VectorPath.Num(); i++){

                UE_LOG(LogTemp, Log, TEXT("Vector Path is: %s. Which is %f away"), *VectorPath.Last(i).ToString(), FVector::Dist(VectorPath.Last(i), Destination));

            }

            UE_LOG(LogTemp, Log, TEXT("VectorPath Num: %i"), VectorPath.Num());

            DrawDebugLine(Worldz, CurrentVector.CurrentVector, Destination, FColor::Green, true, 10.0f, 15, 10.0f);
            UE_LOG(LogTemp, Log, TEXT("Path Found"));
            break;

        }

        OpenVectors.Remove(CurrentVector);
        ClosedVectors.Add(CurrentVector);

        TArray<FVectorValues> Neighbors;

        FRotator RightVector(0, 90, 0);
        FRotator BehindVector = FRotator(0, 180, 0);
        FRotator LeftVector(0, 270, 0);
        FRotator ForwardVector(0, 360, 0);

        UE_LOG(LogTemp, Log, TEXT("Increments: %f"), Increments);

        FVector TraceEndForward = CurrentVector.CurrentVector + (ForwardVector.Vector() * Increments);
        FVector TraceEndLeft = CurrentVector.CurrentVector + (LeftVector.Vector() * Increments);
        FVector TraceEndBehind = CurrentVector.CurrentVector + (BehindVector.Vector() * Increments);
        FVector TraceEndRight = CurrentVector.CurrentVector + (RightVector.Vector() * Increments);

        FHitResult HitForward;
        FHitResult HitLeft;
        FHitResult HitBehind;
        FHitResult HitRight;

        

        if(TraceEndForward != CurrentVector.CurrentVector){

            if(Worldz->LineTraceSingleByChannel(HitForward, CurrentVector.CurrentVector, TraceEndForward, ECC_Visibility, QueryParams)){
                float Forwardh = FVector::Dist(TraceEndForward, Destination)/100.0f;
                FVectorValues Front = FVectorValues(TraceEndForward, Increments, Forwardh, Increments + Forwardh, true);
                if(!ClosedVectors.Contains(Front) && !OpenVectors.Contains(Front)){
                    ClosedVectors.Add(Front);
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndForward, FColor::Blue, true, 10.0f, 10, 10.0f);
                    

                }
                Neighbors.Add(Front);
                
            

            } else {

                float Forwardh = FVector::Dist(TraceEndForward, Destination)/100.0f;
                FVectorValues Front = FVectorValues(TraceEndForward, Increments, Forwardh, Increments + Forwardh, false);
                if(!ClosedVectors.Contains(Front) && !OpenVectors.Contains(Front)){

                    UE_LOG(LogTemp, Log, TEXT("Foward Vector: %s"), *TraceEndForward.ToString());
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndForward, FColor::Red, true, 10.0f, 10, 10.0f);
                    
                }
                Neighbors.Add(Front);
                //OpenVectors.Add(Front);
                
            }

        }
        


        if(TraceEndLeft != CurrentVector.CurrentVector){

            if(Worldz->LineTraceSingleByChannel(HitLeft, CurrentVector.CurrentVector, TraceEndLeft, ECC_Visibility, QueryParams)){
                float Lefth = FVector::Dist(TraceEndLeft, Destination)/100.0f;
                FVectorValues Left = FVectorValues(TraceEndLeft, Increments, Lefth, Increments + Lefth, true);
                if(!ClosedVectors.Contains(Left) && !OpenVectors.Contains(Left)){
                    ClosedVectors.Add(Left);
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndLeft, FColor::Blue, true, 10.0f, 10, 10.0f);
                    
                }
                Neighbors.Add(Left);

                

            } else {

                float Lefth = FVector::Dist(TraceEndLeft, Destination)/100.0f;
                FVectorValues Left = FVectorValues(TraceEndLeft, Increments, Lefth, Increments + Lefth, false);
                if(!ClosedVectors.Contains(Left) && !OpenVectors.Contains(Left)){
                    //OpenVectors.Add(Left);
                    UE_LOG(LogTemp, Log, TEXT("Left Vector: %s"), *TraceEndLeft.ToString());
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndLeft, FColor::Yellow, true, 10.0f, 10, 10.0f);
                    


                }
                Neighbors.Add(Left);
            }

        }
        


        if(TraceEndBehind != CurrentVector.CurrentVector){

            if(Worldz->LineTraceSingleByChannel(HitBehind, CurrentVector.CurrentVector, TraceEndBehind, ECC_Visibility, QueryParams)){
                float Backh = FVector::Dist(TraceEndBehind, Destination)/100.0f;
                FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, Backh, Increments + Backh, true);
                if(!ClosedVectors.Contains(Behind) && !OpenVectors.Contains(Behind)){

                    
                    ClosedVectors.Add(Behind);
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndBehind, FColor::Blue, true, 10.0f, 10, 10.0f);
                }
                Neighbors.Add(Behind);
            } else {

                float Backh = FVector::Dist(TraceEndBehind, Destination)/100.0f;
                FVectorValues Behind = FVectorValues(TraceEndBehind, Increments, Backh, Increments + Backh, false);
                if(!ClosedVectors.Contains(Behind) && !OpenVectors.Contains(Behind)){
                    //OpenVectors.Add(Behind);
                    UE_LOG(LogTemp, Log, TEXT("Behind Vector: %s"), *TraceEndBehind.ToString());
                    //FVector DebugBehind = FVector(TraceEndBehind.X, TraceEndBehind.Y, TraceEndBehind.Z + 50.0f);
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndBehind, FColor::Magenta, true, 10.0f, 10, 10.0f);
                    


                }
                Neighbors.Add(Behind);
                
            }

        }
        


        if(TraceEndRight != CurrentVector.CurrentVector){

            if(Worldz->LineTraceSingleByChannel(HitRight, CurrentVector.CurrentVector, TraceEndRight, ECC_Visibility, QueryParams)){
                float Righth = FVector::Dist(TraceEndRight, Destination)/100.0f;
                FVectorValues Right = FVectorValues(TraceEndRight, Increments, Righth, Increments + Righth, true);
                if(!ClosedVectors.Contains(Right) && !OpenVectors.Contains(Right)){
                    
                    ClosedVectors.Add(Right);
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndRight, FColor::Blue, true, 10.0f, 10, 10.0f);


                }
                Neighbors.Add(Right);

                

            } else {

                float Righth = FVector::Dist(TraceEndRight, Destination)/100.0f;
                FVectorValues Right = FVectorValues(TraceEndRight, Increments, Righth, Increments + Righth, false);
                if(!ClosedVectors.Contains(Right) && !OpenVectors.Contains(Right)){

                    //OpenVectors.Add(Right);
                    UE_LOG(LogTemp, Log, TEXT("Right Vector: %s"), *TraceEndRight.ToString());
                    DrawDebugLine(Worldz, CurrentVector.CurrentVector, TraceEndRight, FColor::Cyan, true, 10.0f, 10, 10.0f);
                    

                }
                Neighbors.Add(Right);
                
            }

        }

        for(int32 i = 0; i <Neighbors.Num(); i++){

            FVectorValues CurrentVectorValue = Neighbors.Last(i);
            AllVectors.Add(CurrentVectorValue);

            if(!ClosedVectors.Contains(CurrentVectorValue) && !CurrentVectorValue.bDidCollide){

                int32 Tempg = CurrentVector.g + 1.0f;

                if(OpenVectors.Contains(CurrentVectorValue)){
                    if(Tempg < CurrentVectorValue.g){

                        CurrentVectorValue.g = Tempg;

                    }


                } else {

                    CurrentVectorValue.g = Tempg;
                    CurrentVectorValue.h = FVector::Dist(CurrentVectorValue.CurrentVector, Destination)/100.0f;
                    CurrentVectorValue.f = CurrentVectorValue.h + CurrentVectorValue.g;
                    OpenVectors.Add(CurrentVectorValue);
                    

                }

                OpenVectors.Last(OpenVectors.Num()-1).PreviousPoint = &CurrentVector;
                
                FVector Temp = OpenVectors.Last(OpenVectors.Num()-1).CurrentVector;

                OpenVectors.Last(OpenVectors.Num()-1).bHasPrevious = true;
                FVectorValues TempOne = OpenVectors.Last(OpenVectors.Num()-1);

                
                

                

                //CurrentVectorValue.PreviousVector = StartVectorValue;

            }

        }
        CrashPrevention++;

    }
    //UE_LOG(LogTemp, Log, TEXT("g: %f"), gMain);

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


