// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SampleCharacter.generated.h"

UCLASS(Blueprintable)
class ASampleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASampleCharacter();

	void BeginPlay();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

/***********************************These Functions Came With the Base UE4 TopDown Code**********************************************/
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
/**************************************************************************************************************************************/

/***********************************Camera and Camera Movement Functions/Variables*****************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraDistance = 1000.0f; //The distance the Camera is from our invisible player (So the ground)

	void MoveVerticle(float val); //The move verticle function called when the Camera wants to move up or down
	void MoveHorizontal(float value); //The move horizontal function called when the Camera wants to move right or left

	bool bIsUsingKeysToMove = false; //A boolean that is used to determine if the player is holding down any of the WASD keys assiociated with activating the above functions

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 10.0f; //The speed at which the camera moves (This is used for Key moving, not edge scrolling)

private:
/***********************************************Components that the Character utilise****************************************************************/
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent; //The camera component

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;//The component that makes the camera sit far above the player

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld; //This is SOLELY for a reliable way to get the player's mouse location relative to world instead of screen

	void SetDecalLocation(); //The function to continuously move the decal to the mouse's location
/*****************************************************************************************************************************************************/

/******************************************************Edge Scrolling Functions and Variables*********************************************************/

	UFUNCTION()
	FVector CursorLocCheck(); //A Function to check the cursor's location every tic

	UPROPERTY()
	float Margin = 15.0f; //The margin that the cursor has to be at least away from the screen's edge for it to start scrolling

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CamSpeed = 1.0f; //The speed of the scroll

private:

	UPROPERTY()
	int32 ScreenX; //The size of the screen in the X position

	UPROPERTY()
	int32 ScreenY; //The size of the screen in the Y position
/******************************************************************************************************************************************************/

/**************************************************************************Misc.***********************************************************************/

	class APlayerController* PC; //The player controller that the player is using (declared elsewhere)



};

