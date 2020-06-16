// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
AWeaponComponent::AWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	// ...
}


// Called when the game starts
void AWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void AWeaponComponent::Fire(){

 	//Muzzle effect, like a flash
	if(MuzzleEffect){

		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh, MuzzleSocketName);

    }

    //Bullet Trace effect
    if(TracerEffect){

        FVector SocketLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName); 
        FRotator SocketRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);

        FCollisionQueryParams QueryParams; //Making the Query parameters
	    //QueryParams.AddIgnoredActor(MyOwner); //Making it ignore the owner for collision
	    QueryParams.AddIgnoredActor(GetOwner()); //So it doesnt hit the gun
	    QueryParams.bTraceComplex = true; 
	    QueryParams.bReturnPhysicalMaterial = true;

        FVector SetDirection = SocketRotation.Vector();

        //Making the line to check for the actual collision
	    FVector TraceEnd = SocketLocation + (SetDirection * 10000); //Big number so big range

        //Particle "Target" parameter
		FVector TracerPointEnd = TraceEnd;

        //Declaring the hit Result
		FHitResult HitObject;

        GetWorld() -> LineTraceSingleByChannel(HitObject, SocketLocation, TraceEnd, ECC_Visibility, QueryParams);
		

	    //Making the particle system
	    UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(), TracerEffect, SocketLocation
	    );
	    if(TracerComp){
	    	//if we have a tracer effect we play it
	    	TracerComp->SetVectorParameter(TracerTargetName, TracerPointEnd);

	    }

		//Playing the fire sound, if we have it
	    if (FireSound != NULL){

	    	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetOwner()->GetActorLocation());

    	}

	}
   

}

