// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SAMPLE_API FVectorValues
{
public:
	FVectorValues(FVector CurrentVecto, float PathWeigh, float Distanc, float OverallWeigh, FVector PreviousVecto, bool bDidCollid);
	~FVectorValues();

	UPROPERTY()
	FVector CurrentVector;

	UPROPERTY()
	float PathWeight = 0.0f;

	UPROPERTY()
	float Distance = 0.0f;

	UPROPERTY()
	float OverallWeight = 0.0f;

	UPROPERTY()
	FVector PreviousVector;

	UPROPERTY()
	bool bDidCollide;
};
