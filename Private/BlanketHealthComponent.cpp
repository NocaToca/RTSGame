// Fill out your copyright notice in the Description page of Project Settings.


#include "BlanketHealthComponent.h"

// Sets default values for this component's properties
UBlanketHealthComponent::UBlanketHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBlanketHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlanketHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBlanketHealthComponent::TakeDamage(float damage){

	

	if(damage == 0){

		return;

	} else if(UnitHealth - damage <= 0){

		UnitHealth = 0;
		UE_LOG(LogTemp, Log, TEXT("Ded"));
		return;

	} else {

		UE_LOG(LogTemp, Warning, TEXT("%f"), damage);
		UnitHealth -= damage;
		return;

	}

	

}

