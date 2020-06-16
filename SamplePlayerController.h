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

	ABlanketActor* SelectedActor;

	void DeSelect();

	ASampleCharacter* MyOwner;

	/** Navigate player to the current mouse cursor location. */


	/** Navigate player to the given world location. */


	/** Input handlers for SetDestination action. */

	void VerticleMovement(float val);
	
	void HorizontalMovement(float value);

	void Interact();

	void CommandMove();

	// void MoveCharacter();
};


