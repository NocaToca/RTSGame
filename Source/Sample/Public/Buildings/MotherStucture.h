// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BlanketBuildings.h"
#include "MotherStucture.generated.h"

/**
 * 
 */
class USkeletalMeshComponent;
UCLASS()
class SAMPLE_API AMotherStucture : public ABlanketBuildings
{
	GENERATED_BODY()

public:

	AMotherStucture();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	bool InRange(FVector Vector);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	float BuildingRadius = 100.0f;

};
