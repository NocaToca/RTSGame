// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BlanketBuildings.h"
#include "HumanInfantryBuilding.generated.h"

/**
 * 
 */
class AHumanMarineUnit;
UCLASS()
class SAMPLE_API AHumanInfantryBuilding : public ABlanketBuildings
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHumanInfantryBuilding();

	//The overidden function for ClickedOnBuilding
	virtual void ClickedOnBuilding(ASamplePlayerController* PlayerController) override;

/*****************************************************Spawning and interacting*************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Units")
	void CreateMarineUnit(); //The function that is called to create a marine unit

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<AHumanMarineUnit> StarterMarineClass; //The marine class that the building will be making

	FActorSpawnParameters SpawnParams; //The spawning params

	bool BuildUnit();

	FTimerHandle MarineSpawn;

/*******************************************************************************************************************************************/

/*************************************************************Composition for the building**************************************************/
	//The skeletal mesh for things
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

	

/********************************************************************************************************************************************/

/***************************************************************Units************************************************************************/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pricing")
	float InfantryQEPrice = 50.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pricing")
	float InfantryAEPrice = 0.0f;

/********************************************************************************************************************************************/

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};