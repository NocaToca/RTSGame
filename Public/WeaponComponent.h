// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WeaponComponent.generated.h"

class UParticleSystem;
class USoundBase;
class USkeletalMeshComponet;
UCLASS()
class SAMPLE_API AWeaponComponent : public APawn
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AWeaponComponent();

	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particles")
	UParticleSystem* TracerEffect;

	//Sound base
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	USoundBase* FireSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sockets")
	FName MuzzleSocketName = "WeaponSocket";

	FName TracerTargetName = "Target";

public:	
	// Called every frame

		
};
