// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlanketActor.h"
#include "BlanketUnits.generated.h"

class UPawnSensingComponent;
class ABlanketActor;
UCLASS()
class SAMPLE_API ABlanketUnits : public ABlanketActor
{
	GENERATED_BODY()

	
public:

	float BaseDamage = 1.0f;

	float DamageVariance = .5f;

	float AttackRate = 1.0f;

	float CalculateDamage();

	virtual void BeginPlay() override;

	virtual void Attack(ABlanketActor* HitActor);

	ABlanketUnits();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	
	void MoveUnit(FVector WhereToMove);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* SenseComp;

protected:

	

};
