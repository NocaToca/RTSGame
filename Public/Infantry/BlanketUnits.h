// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlanketActor.h"
#include "BlanketUnits.generated.h"

class UPawnSensingComponent;
class ABlanketActor;
class  AIAlgorithm;
UCLASS()
class SAMPLE_API ABlanketUnits : public ABlanketActor
{
	GENERATED_BODY()

	
public:

	virtual void BeginPlay() override;

	ABlanketUnits();

/*********************************************Combat Variables/Functions*************************************************/
	float BaseDamage = 1.0f;

	float DamageVariance = .5f;

	float AttackRate = 1.0f;

	float CalculateDamage();

	virtual void Attack(ABlanketActor* HitActor);

/*************************************************************************************************************************/

/********************************************************AI Functions/Variables*******************************************/
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	
	void MoveUnit(FVector WhereToMove, UWorld* Worldz);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* SenseComp;

	AIAlgorithm* algorithms; 

/***************************************************************************************************************************/

protected:


	

};
