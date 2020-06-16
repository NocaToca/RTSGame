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

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraDistance = 1000.0f;

	void MoveVerticle(float val);
	void MoveHorizontal(float value);

	bool bIsUsingKeysToMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 10.0f;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	class APlayerController* PC;

	UFUNCTION()
	FVector CursorLocCheck();

	UPROPERTY()
	float Margin = 15.0f;

	UPROPERTY()
	float CamSpeed = 1.0f;

	UPROPERTY()
	int32 ScreenX;

	UPROPERTY()
	int32 ScreenY;




};

