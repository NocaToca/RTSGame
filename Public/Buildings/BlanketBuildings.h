// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlanketActor.h"
#include "BlanketBuildings.generated.h"

/**
 * 
 */

UCLASS()
class SAMPLE_API ABlanketBuildings : public ABlanketActor
{
	GENERATED_BODY()


public:

	//The function to restrict movement
	UFUNCTION(BlueprintCallable, Category = "Building")
	void RestictMovement(ASamplePlayerController* PlayerController);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Click")
	ASamplePlayerController* CurrentPlayerController;

	


	
	
};
