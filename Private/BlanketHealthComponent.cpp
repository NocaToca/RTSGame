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

//A simple function that takes in the damage and then based off of that damage checks to see if the unit died
void UBlanketHealthComponent::TakeDamage(float damage){

	

	if(damage == 0){
		//If the damage is 0, we dont need to do anything
		return;

	} else if(UnitHealth - damage <= 0){
		//If the unit is going to die, set it's health to zero and then run the death function (to be implemented)
		UnitHealth = 0;
		UE_LOG(LogTemp, Log, TEXT("Ded")); //Debug Line
		return;

	} else {
		//Just take damage equal to the damage otherwise
		UE_LOG(LogTemp, Warning, TEXT("%f"), damage);//Debug Line
		UnitHealth -= damage;
		return;

	}

	

}

