// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// USTRUCT()
// struct FVectorValues{


// public:

// 	UPROPERTY()
// 	FVector CurrentVector;

// 	UPROPERTY()
// 	float PathWeight = 0.0f;

// 	UPROPERTY()
// 	float Distance = 0.0f;

// 	UPROPERTY()
// 	float OverallWeight = 0.0f;

// 	UPROPERTY()
// 	FVector PreviousVector;

// };
class FVectorValues;
class AActor;
/**
 * 
 */
class SAMPLE_API AIAlgorithm
{
public:
	AIAlgorithm();
	~AIAlgorithm();

	TArray<FVector> PathfindingArray;

	void Pathfind(AActor* Actor, FVector Destination, UWorld World);

	float RayTrace(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, UWorld World);

	float RayTraceExtended(FVector StartingVector, float Increments, TArray<FVectorValues> VectorPath, FVector Destination, TArray<FVectorValues> AllVectors, AActor* MovingActor, float PathWeight, float IncrementWeight, UWorld World);

};
