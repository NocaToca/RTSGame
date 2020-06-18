// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SAMPLE_API FVectorValues
{
public:
	FVectorValues(FVector CurrentVecto, float PathWeigh, float Distanc, float OverallWeigh, bool bDidCollid);
	~FVectorValues();

	UPROPERTY()
	FVector CurrentVector;

	UPROPERTY()
	float g = 0.0f;

	UPROPERTY()
	float h = 0.0f;

	UPROPERTY()
	float f = 0.0f;

	// UPROPERTY()
	//FVector PreviousVector;

	UPROPERTY()
	bool bDidCollide;

	bool bHasPrevious = false;

	FVectorValues* PreviousPoint;

	void AddNeighbors(FVector Neighbor);

	inline bool operator==(const FVectorValues& rhs) const{
		if(this->CurrentVector == rhs.CurrentVector){
			if(this->g == rhs.g){
				if(this->h == rhs.h){
					if(this->f == rhs.f){
						
					}
				}
			}
			return true;

		}
		return false;

	}

	
	TArray<FVector> Neighbors;
};
