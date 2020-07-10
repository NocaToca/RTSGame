// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SamplePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SampleCharacter.h"
#include "Engine/World.h"
#include "BlanketActor.h"
#include "Infantry/BlanketUnits.h"
#include "Buildings/BlanketBuildings.h"
#include "Buildings/HumanInfantryBuilding.h"
#include "Buildings/HumanQuintessenceBuilding.h"
#include "Buildings/HumanAetherBuilding.h"
#include "Buildings/MotherStucture.h"
#include "Kismet/GameplayStatics.h"

ASamplePlayerController::ASamplePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	//We only need to show the mouse cursor so you can tell where you're clicking/if you're about to edge scroll
	
}

void ASamplePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//we keep updating the destination every tick while desired
	
	
	
}

void ASamplePlayerController::BeginPlay(){

	Super::BeginPlay();

	//Setting what pawn this player controller is controller
	MyOwner = Cast<ASampleCharacter>(GetPawn());

	//And then making sure that the cast actually worked. 
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

	//Ineracting with Buildings/Units
	InputComponent->BindAction("Interact", IE_Released, this, &ASamplePlayerController::Interact);
	InputComponent->BindAction("DeSelect", IE_Released, this, &ASamplePlayerController::DeSelect);
	InputComponent->BindAction("CommandMove", IE_Released, this, &ASamplePlayerController::CommandMove);

	//Walking Components and movement:
	InputComponent->BindAxis("WalkVertical", this, &ASamplePlayerController::VerticleMovement); //Verticle movement (Up and Down)
	InputComponent->BindAxis("WalkHorizontal", this, &ASamplePlayerController::HorizontalMovement); //Horizontal movemnt (left and right)

	
}

//When the player right clicks, this function is ran to check what is under the cursor (by checking whats under the decal component) and then
//Checking to see if that thing is either a building or a unit
void ASamplePlayerController::Interact(){

	if(SelectedActor){

		SelectedActor->bClickedOn = false;

	}
	

	if(bBuildingBuilding){

		TArray<AActor*> Structures;
		
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), DefaultStructureClass, Structures);

		for(int32 i = 0; i < Structures.Num(); i++){

			AMotherStucture* StructureAssessing = Cast<AMotherStucture>(Structures.Last(i));

			if(StructureAssessing){

				if(StructureAssessing->InRange(MyOwner->CursorToWorld->GetComponentLocation())){

					break;

				} else if(i == Structures.Num()-1){

					return;

				}


			}

			
		}

		FVector SpawningLocation = MyOwner->CursorToWorld->GetComponentLocation();

		MyOwner->CursorToWorld->DecalSize = FVector::ZeroVector;

		bBuildingBuilding = false;

		ABlanketBuildings* Building;

		if(BuildingToBuild == 0){

			Building = GetWorld()->SpawnActor<AHumanQuintessenceBuilding>(HumanQuintEssenceBuilding, SpawningLocation, FRotator::ZeroRotator, SpawnParams);

			if(Building){

				Building->OwningPlayer = this;

			}

		} else if(BuildingToBuild == 1){

			Building =GetWorld()->SpawnActor<AHumanInfantryBuilding>(HumanInfantryBuilding, SpawningLocation, FRotator::ZeroRotator, SpawnParams);

			if(Building){

				Building->OwningPlayer = this;

			}

		}

		

	}

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

	//These two lines just basically get the hit result under the cursor to see what's under it
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, true, Hit);

	//Checking to see if the hit was actually blocking (AKA it collided with something)
	if (Hit.bBlockingHit){
		
		// We hit something, move there
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.Actor->GetName()); //Debug to see what we clicked on

		//Checks to see if the object is something that we can interact with
		ABlanketActor* ObjectInGame = Cast<ABlanketActor>(Hit.Actor); 
		if(ObjectInGame){

			//If it is, we return the type of the actor (See the BlanketActor code for return types) and does specific things based off of the type
			int32 ObjectType = ObjectInGame->ObjectType(ObjectInGame);
			if(ObjectType == 0){
				//The Object is a building
				UE_LOG(LogTemp, Warning, TEXT("Ref008")); //Debug Line
				ObjectInGame->ClickedOnBuilding(this); //Runs the relatively function for the building while passing in the player controller so it can
				//Restrict its movement until the building menu is exited 
				ChangeSelectedActor(ObjectInGame); //Changes the selected actor to the building

			} else if(ObjectType == 1){
				//The object is a unit
				UE_LOG(LogTemp, Warning, TEXT("Ref009")); //Debug Line
				ObjectInGame->ClickedOn(); //The general clicked on function that doesn't need any pass ins
				ChangeSelectedActor(ObjectInGame); //Changes the selected actor to this unit

			}
			//UE_LOG(LogTemp, Warning, TEXT("Object Casted")); //Debug Line
			

		}
	}

}

//Changes the selected actor
void ASamplePlayerController::ChangeSelectedActor(ABlanketActor* NewSelectedActor){

	//If there is already a selected actor, we have to make sure to tell it we are no longer interacting with it
	if(SelectedActor){

		SelectedActor->bClickedOn = false;

	}
	
	SelectedActor = NewSelectedActor; //Setting the selected actor to the new actor

}

void ASamplePlayerController::DeSelect(){

	if(bBuildingBuilding){

		bBuildingBuilding = false;

		MyOwner->CursorToWorld->DecalSize = FVector::ZeroVector;

	}

	if(SelectedActor){

		SelectedActor->bClickedOn = false;
		
	}

	

}

//Activates when the player holds down W or S
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

//Activates when the player holds down A or D
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

//Commanding the selected actor to move to the spot under the mouse
void ASamplePlayerController::CommandMove(){

	//UE_LOG(LogTemp, Warning, TEXT("Ref001")); //Debug Line

	//Checks to see if there actually is a selected Actor and then moves the selected actor if they aren't a building
	if(SelectedActor){

		//UE_LOG(LogTemp, Warning, TEXT("Ref002")); //Debug Line

		int32 ActorType = SelectedActor->ObjectType(SelectedActor); //Returns the object type
		//UE_LOG(LogTemp, Warning, TEXT("%i"), ActorType);//Debug Line

		//If the actor is not a building, we're moving it
		if(ActorType != 0){

			//UE_LOG(LogTemp, Warning, TEXT("Ref003")); //Debug Line
			ABlanketUnits* Unit = Cast<ABlanketUnits>(SelectedActor);//We cast it to a unit function so we can move it

			FVector DecalPos = MyOwner->GetCursorToWorld()->GetComponentLocation(); //Getting the decal location

			Unit->MoveUnit(DecalPos, GetWorld()); //Moving the unit to the decal location

		}

	}

}


void ASamplePlayerController::BuildBuilding(int32 BuildingType){

	if(SelectedActor){

		SelectedActor->bClickedOn = false;

	}

	BuildingToBuild = BuildingType;

	MyOwner->CursorToWorld->DecalSize = FVector(30.0f, 30.0f, 1.0f);

	bBuildingBuilding = true;

}