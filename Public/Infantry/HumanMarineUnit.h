// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Infantry/BlanketUnits.h"
#include "HumanMarineUnit.generated.h"

/**
 * 
 */
class USkeletalMeshComponet;
class ABlanketComponet;
class UInfantryHealthComp;
class AWeaponComponent;
UCLASS()
class SAMPLE_API AHumanMarineUnit : public ABlanketUnits
{
	GENERATED_BODY()

public:

	AHumanMarineUnit();

	virtual void BeginPlay() override;
/*******************************************************************Combat Functions*************************************************/
	virtual void Attack(ABlanketActor* HitActor) override;

	FTimerHandle FireDelay;

	float FireRate = 6000.0f;

/*************************************************************************************************************************************/

/****************************************************************Components/Meshes****************************************************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UInfantryHealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeaponComponent* WeaponComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* MeshToAttachTo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* MainMesh;

/***************************************************************************************************************************************/

/****************************************************************Misc.******************************************************************/
	FActorSpawnParameters SpawnParams;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AWeaponComponent> StarterWeaponClass;

/****************************************************************************************************************************************/

protected:

	void RotateToVictim(ABlanketActor* HitActor);

	


private:



	
};
