// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfantryBuilding.generated.h"

class USkeletalMeshComponent;
UCLASS()
class SAMPLE_API AInfantryBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInfantryBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ClickedOn();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
