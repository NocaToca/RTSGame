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
	float PathWeight = 0.0f;

	UPROPERTY()
	float Distance = 0.0f;

	UPROPERTY()
	float OverallWeight = 0.0f;

	// UPROPERTY()
	// FVectorValues PreviousVector;

	UPROPERTY()
	bool bDidCollide;

	void AddNeighbors(FVector Neighbor);

	inline bool operator==(const FVectorValues& rhs) const{
		if(this->CurrentVector == rhs.CurrentVector){
			if(this->PathWeight == rhs.PathWeight){
				if(this->Distance == rhs.Distance){
					if(this->OverallWeight == rhs.OverallWeight){
						return true;
					}
				}
			}

		}
		return false;

	}

	
	TArray<FVector> Neighbors;
};
