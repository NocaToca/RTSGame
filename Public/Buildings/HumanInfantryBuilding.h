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

	UFUNCTION(BlueprintCallable, Category = "Units")
	void CreateMarineUnit();

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<AHumanMarineUnit> StarterMarineClass;

	FActorSpawnParameters SpawnParams;

	//The skeletal mesh for things
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};