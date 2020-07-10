// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BlanketBuildings.h"
#include "HumanQuintessenceBuilding.generated.h"

/**
 * 
 */
class ASamplePlayerController;
class USkeletalMeshComponent;
UCLASS()
class SAMPLE_API AHumanQuintessenceBuilding : public ABlanketBuildings
{
	GENERATED_BODY()

public:

	AHumanQuintessenceBuilding();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Buildings")
	void OnBuilt(ASamplePlayerController* MyOwner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float QuintessenceGeneration = 1.0f;

	
	
};
