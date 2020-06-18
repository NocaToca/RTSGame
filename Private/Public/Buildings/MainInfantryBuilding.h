// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlanketBuildings.h"
#include "MainInfantryBuilding.generated.h"

class USkeletalMeshComponent;
UCLASS()
class SAMPLE_API AMainInfantryBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainInfantryBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ClickedOn();

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
