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

	

	FORCEINLINE void Pathfind(AActor* Actor, FVector Destination, UWorld* World);

	float RayTrace(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> OpenVectors, AActor* MovingActor, UWorld* World, TArray<FVectorValues> ClosedVectors, FVectorValues StartVectorValue);

	float RayTraceExtended(FVector StartingVector, float Increments, TArray<FVector> VectorPath, FVector Destination, TArray<FVectorValues> OpenVectors, AActor* MovingActor, float PathWeight, float IncrementWeight, UWorld* World, float NumberOfPaths, FVector MainStartingVector, FVector PreviousVector, TArray<FVectorValues> ClosedVectors, FVectorValues StartVectorValue);

	bool FVectorEstimate(FVector LocationOne, FVector LocationTwo, float Threshold);

	void VectorPathing(TArray<FVector> VectorPath, TArray<FVectorValues> OpenVectors, FVectorValues EndingVector, UWorld* Worldz, FVector StartingVector);

	FVector FindLastVectorInDirection(FRotator Direction, TArray<FVector> VectorPath, float Increments);
	
	FRotator Find2DDirection(FVector FirstVector, FVector PreviousVector);

};