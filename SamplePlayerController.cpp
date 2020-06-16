// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SamplePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SampleCharacter.h"
#include "Engine/World.h"
#include "BlanketActor.h"
#include "Infantry/BlanketUnits.h"

ASamplePlayerController::ASamplePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
}

void ASamplePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	
	
	
}

void ASamplePlayerController::BeginPlay(){

	Super::BeginPlay();

	MyOwner = Cast<ASampleCharacter>(GetPawn());
	if(MyOwner){

		UE_LOG(LogTemp, Warning, TEXT("Ref006"));

	} else {

		UE_LOG(LogTemp, Error, TEXT("SampleCharacter did not cast!"));

	}


}

void ASamplePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Released, this, &ASamplePlayerController::Interact);
	InputComponent->BindAction("DeSelect", IE_Released, this, &ASamplePlayerController::DeSelect);
	InputComponent->BindAction("CommandMove", IE_Released, this, &ASamplePlayerController::CommandMove);

	//Walking Components and movement:
	InputComponent->BindAxis("WalkVertical", this, &ASamplePlayerController::VerticleMovement); //Verticle movement (Up and Down)
	InputComponent->BindAxis("WalkHorizontal", this, &ASamplePlayerController::HorizontalMovement); //Horizontal movemnt (left and right)

	
}

void ASamplePlayerController::Interact(){

	// UE_LOG(LogTemp, Warning, TEXT("Click"));

	// ASampleCharacter* MyPawn = Cast<ASampleCharacter>(GetOwner());

	// FVector TraceStart = MyPawn->GetCursorToWorld()->GetComponentLocation();
	// FVector TraceEnd = TraceStart;
	// TraceEnd.Z *= -10000.0f;

	// FCollisionQueryParams QueryParams;
	// QueryParams.AddIgnoredActor(MyPawn); 
	// QueryParams.AddIgnoredActor(this);
	// QueryParams.bTraceComplex = true; 
	// QueryParams.bReturnPhysicalMaterial = true;

	// FHitResult HitResult;

	// if(GetWorld() -> LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams)){
			
	// 	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	// }

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);

	if (Hit.bBlockingHit)
	{
		
		// We hit something, move there
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.Actor->GetName());
		ABlanketActor* ObjectInGame = Cast<ABlanketActor>(Hit.Actor);
		if(ObjectInGame){

			int32 ObjectType = ObjectInGame->ObjectType(ObjectInGame);
			if(ObjectType == 0){

				UE_LOG(LogTemp, Warning, TEXT("Ref008"));
				ObjectInGame->ClickedOnBuilding(this);
				ChangeSelectedActor(ObjectInGame);

			} else if(ObjectType == 1){

				UE_LOG(LogTemp, Warning, TEXT("Ref009"));
				ObjectInGame->ClickedOn();
				ChangeSelectedActor(ObjectInGame);

			}
			UE_LOG(LogTemp, Warning, TEXT("Object Casted"));
			

		}
	}

}

void ASamplePlayerController::ChangeSelectedActor(ABlanketActor* NewSelectedActor){

	if(SelectedActor){

		SelectedActor->bClickedOn = false;

	}
	
	SelectedActor = NewSelectedActor;

}

void ASamplePlayerController::DeSelect(){

	SelectedActor->bClickedOn = false;

}

void ASamplePlayerController::VerticleMovement(float val){

	//UE_LOG(LogTemp, Warning, TEXT("Ref005"));
	//Obviously just keeps adding/subtracting one to the movement vector until the player stops holding down a key
	if(val == 0){

		MyOwner->bIsUsingKeysToMove = false;
		return;

	}


	if(MyOwner){

		MyOwner->MoveVerticle(val);

	}
	

}

void ASamplePlayerController::HorizontalMovement(float value){

	//UE_LOG(LogTemp, Warning, TEXT("Ref004"));
	//Obviously just keeps adding/subtracting one to the movement vector until the player stops holding down a key
	if(value == 0){

		MyOwner->bIsUsingKeysToMove = false;
		return;

	}

	if(MyOwner){

		MyOwner->MoveHorizontal(value);

	}
	

}

void ASamplePlayerController::CommandMove(){

	UE_LOG(LogTemp, Warning, TEXT("Ref001"));
	if(SelectedActor){

		UE_LOG(LogTemp, Warning, TEXT("Ref002"));
		int32 ActorType = SelectedActor->ObjectType(SelectedActor);
		UE_LOG(LogTemp, Warning, TEXT("%i"), ActorType);
		if(ActorType != 0){

			UE_LOG(LogTemp, Warning, TEXT("Ref003"));
			ABlanketUnits* Unit = Cast<ABlanketUnits>(SelectedActor);

			FVector DecalPos = MyOwner->GetCursorToWorld()->GetComponentLocation();

			Unit->MoveUnit(FVector(DecalPos.X, DecalPos.Y, DecalPos.Z));

		}

	}

}
