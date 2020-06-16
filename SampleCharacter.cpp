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

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector::ZeroVector;
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASampleCharacter::BeginPlay(){

	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());

	PC->GetViewportSize(ScreenX, ScreenY);
}

void ASampleCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if(bIsUsingKeysToMove == false){

		AddActorWorldOffset(CursorLocCheck() * CamSpeed);

	}
	

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

FVector ASampleCharacter::CursorLocCheck(){

	float MousePosX;
	float MousePosY;
	float CameraPosX = 0.0f;
	float CameraPosY = 0.0f;

	PC->GetMousePosition(MousePosX, MousePosY);

	if(MousePosX <= Margin){

		CameraPosY = -1.0f;

	}

	if(MousePosY <= Margin){

		CameraPosX = 1.0f;

	}

	if(MousePosX >= ScreenX - Margin){

		CameraPosY = 1.0f;

	}

	if(MousePosY >= ScreenY - Margin){

		CameraPosX = -1.0f;

	}

	if(MousePosX == 0 && MousePosY == 0){
		
		CameraPosX = 0.0f;
		CameraPosY = 0.0f;

	}

	return FVector(CameraPosX, CameraPosY, 0);

}

void ASampleCharacter::MoveVerticle(float val){

	UE_LOG(LogTemp, Log, TEXT("val: %f"), val);

if(val != 0.0f){

	bIsUsingKeysToMove = true;
	AddActorWorldOffset(FVector(val * MoveSpeed, 0, 0));
	return;

}
bIsUsingKeysToMove = false;
}

void ASampleCharacter::MoveHorizontal(float value){

	UE_LOG(LogTemp, Log, TEXT("value: %f"), value);

if(value != 0.0f){

	bIsUsingKeysToMove = true;
	AddActorWorldOffset(FVector(0, value * MoveSpeed, 0));
	return;

}
bIsUsingKeysToMove = false;
}