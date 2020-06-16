// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SampleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ASampleCharacter::ASampleCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = CameraDistance;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Setting up the decal component to be attached to the mouse
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector::ZeroVector; //I don't want to see the decal, so we make it invisible by it having no size
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASampleCharacter::BeginPlay(){

	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController()); //On the start of a game, we get the player controller

	PC->GetViewportSize(ScreenX, ScreenY); //And then get the screen size from it
}

void ASampleCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	//Checks to see if the player is using their keys to move the camera and if not, enables edge scrolling
	if(bIsUsingKeysToMove == false){

		AddActorWorldOffset(CursorLocCheck() * CamSpeed); //Takes a FVector and adds it to the character's location

	}
	
	SetDecalLocation(); //Setting the decal location to the mouse
	
}

void ASampleCharacter::SetDecalLocation(){

	//This is basically a really fancy way to set the decal location, but UE4 started me off with this so I don't really need to edit it or make my own way
	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}	

}

/*This function is to check where if the location of the cursor relative to the screen is in a spot on the screen at which
the screen should start scrolling. These spots would be the edges, hence edge scrolling
For reference, the top left of the screen is considered 0,0*/
FVector ASampleCharacter::CursorLocCheck(){

	float MousePosX; //The X position of the mouse
	float MousePosY; //The Y position of the mouse
	float CameraPosX = 0.0f; //Where the camera should move in the X
	float CameraPosY = 0.0f; //Where the camera should move in the Y

	//This is an out function, setting those two variables to what we previously stated them to hold
	PC->GetMousePosition(MousePosX, MousePosY);

	//Checks to see if the screen should move left
	if(MousePosX <= Margin){

		CameraPosY = -1.0f;

	}

	//Checks to see if the screen should move up
	if(MousePosY <= Margin){

		CameraPosX = 1.0f;

	}

	//Checks to see if the screen should move right
	if(MousePosX >= ScreenX - Margin){

		CameraPosY = 1.0f;

	}

	//Checks to see if the screen should move down
	if(MousePosY >= ScreenY - Margin){

		CameraPosX = -1.0f;

	}

	//If the mouse moves out of the screen, the GetMousePostion() function returns 0 for both, so we just disable the edge scroll if thats the case
	if(MousePosX == 0 && MousePosY == 0){
		
		CameraPosX = 0.0f;
		CameraPosY = 0.0f;

	}

	return FVector(CameraPosX, CameraPosY, 0); //Returning the values as an FVector to add 

}

//The verticle (W and S keys) movement function
void ASampleCharacter::MoveVerticle(float val){

	//UE_LOG(LogTemp, Log, TEXT("val: %f"), val); //Debug Line

	//If val is not zero, we add val to the x coordinate vector
	if(val != 0.0f){

		bIsUsingKeysToMove = true; //Set that we are using keys to move to true
		AddActorWorldOffset(FVector(val * MoveSpeed, 0, 0)); //Adding the vector
		return;

	}
	bIsUsingKeysToMove = false; //Otherwise set it to false
}

//The horizontal (A and D keys) movement function
void ASampleCharacter::MoveHorizontal(float value){

	//UE_LOG(LogTemp, Log, TEXT("value: %f"), value);//Debug Line

	//If value is not zero, we add value to the y coordinate vector of the actor
	if(value != 0.0f){

		bIsUsingKeysToMove = true; //Set that we are using keys to move to true
		AddActorWorldOffset(FVector(0, value * MoveSpeed, 0)); //Adding the vector
		return;

	}
	bIsUsingKeysToMove = false; //Otherwise set it to false
}