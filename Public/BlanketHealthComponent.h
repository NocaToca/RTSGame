// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlanketHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLE_API UBlanketHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBlanketHealthComponent();
/************************************************************Health And Damage Components******************************************************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float UnitHealth = 100.0f; //The health that the wearer has

	UFUNCTION()
	void TakeDamage(float damage); //The function that tells the wearer of this component to take damage
/**********************************************************************************************************************************************/

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
