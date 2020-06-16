// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SamplePlayerController.generated.h"

class ABlanketActor;
class ASampleCharacter;
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
/****************************************************************************************************************************************/
	
/*******************************************************Movement Functions***************************************************************/
	void VerticleMovement(float val);
	
	void HorizontalMovement(float value);
/***********************************************************Misc.************************************************************************/

	ASampleCharacter* MyOwner;
/****************************************************************************************************************************************/
	// void MoveCharacter();
};


