// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SamplePlayerController.generated.h"

class ABlanketActor;
class ABlanketBuildings;
class ASampleCharacter;
class AHumanQuintessenceBuilding;
class AHumanInfantryBuilding;
class AHumanAetherBuilding;
class AMotherStucture;
UCLASS()
class ASamplePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASamplePlayerController();

	void ChangeSelectedActor(ABlanketActor* NewSelectedActor);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

/*******************************************Interacting With the Buildings and Units****************************************************/
	ABlanketActor* SelectedActor;

	void DeSelect();

	void Interact();

	void CommandMove();

	FActorSpawnParameters SpawnParams;

	UFUNCTION(BlueprintCallable, Category = "Buildings")
	void BuildBuilding(int32 BuildingType);
	UPROPERTY(EditDefaultsOnly, Category = "Buildings")
	TSubclassOf<AHumanQuintessenceBuilding> HumanQuintEssenceBuilding; //0 = Quintessence Building 
	UPROPERTY(EditDefaultsOnly, Category = "Buildings")
	TSubclassOf<AHumanInfantryBuilding> HumanInfantryBuilding; //1 = Infantry Building
	UPROPERTY(EditDefaultsOnly, Category = "Buildings")
	TSubclassOf<AHumanAetherBuilding> HumanAetherBuilding; //2 = Aether Building

	int32 BuildingToBuild;

	bool bBuildingBuilding = false;
/****************************************************************************************************************************************/
	
/*******************************************************Movement Functions***************************************************************/
	void VerticleMovement(float val);
	
	void HorizontalMovement(float value);
/****************************************************************************************************************************************/

/**********************************************************Resources*********************************************************************/
public:

	float Quintessence = 0.0f;

	float Aether = 0.0f;
private:
/****************************************************************************************************************************************/

/***********************************************************Misc.************************************************************************/
public:
	ASampleCharacter* MyOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buildings")
	TSubclassOf<AMotherStucture> DefaultStructureClass;
/****************************************************************************************************************************************/
	// void MoveCharacter();
};


