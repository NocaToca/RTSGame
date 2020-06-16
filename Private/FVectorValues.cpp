// Fill out your copyright notice in the Description page of Project Settings.


#include "FVectorValues.h"

FVectorValues::FVectorValues(FVector CurrentVecto, float PathWeigh, float Distanc, float OverallWeigh, FVector PreviousVecto)
{
    CurrentVector = CurrentVecto;
    PathWeight = PathWeigh;
    Distance = Distanc;
    OverallWeight = OverallWeigh;
    PreviousVector = PreviousVecto;

}

FVectorValues::~FVectorValues()
{
}
