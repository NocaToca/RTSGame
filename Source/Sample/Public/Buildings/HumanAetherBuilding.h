// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BlanketBuildings.h"
#include "HumanAetherBuilding.generated.h"

/**
 * 
 */
class USkeletalMeshComponent;
UCLASS()
class SAMPLE_API AHumanAetherBuilding : public ABlanketBuildings
{
	GENERATED_BODY()

public: 

	AHumanAetherBuilding();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Buildings")
	void OnBuilt(ASamplePlayerController* MyOwner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
	float AetherGeneration = 1.0f;
	
};
