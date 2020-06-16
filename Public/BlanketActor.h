// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlanketActor.generated.h"

class ASamplePlayerController;
UCLASS()
class SAMPLE_API ABlanketActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlanketActor();
	virtual void ClickedOn() {UE_LOG(LogTemp, Log, TEXT("Clicked!"));}; //Normal clicked on Function for everything but buildings

	//Buildings need to restict the player's movement while it their UI, so they need the player controller
	virtual void ClickedOnBuilding(ASamplePlayerController* PlayerController){UE_LOG(LogTemp, Log, TEXT("Clicked!"));};

	
	//The clicked on boolean (called in blueprints so the UIs work)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Click")
	bool bClickedOn = false;

	//The clicked on function that returns the boolean (called in blueprints so the UIs work)
	UFUNCTION(BlueprintCallable, Category = "Building")
	bool IsClickedOn() { return bClickedOn; };
	

	//0 for buildings, 1 for infantry
	int32 ObjectType(ABlanketActor* Object);

	bool bHasHealthComp = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
