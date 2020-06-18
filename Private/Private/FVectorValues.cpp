// Fill out your copyright notice in the Description page of Project Settings.


#include "FVectorValues.h"

FVectorValues::FVectorValues(FVector CurrentVecto, float PathWeigh, float Distanc, float OverallWeigh, bool bDidCollid)
{
    CurrentVector = CurrentVecto;
    //PreviousVector = PreviousVecto;
    bDidCollide = bDidCollid;

}

FVectorValues::~FVectorValues()
{
}

void FVectorValues::AddNeighbors(FVector Neighbor){

    Neighbors.Add(Neighbor);

}
