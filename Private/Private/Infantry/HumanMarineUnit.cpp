// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanMarineUnit.h"
#include "Components/SkeletalMeshComponent.h"
#include "BlanketActor.h"
#include "Infantry/Components/InfantryHealthComp.h"
#include "WeaponComponent.h"
#include "BlanketHealthComponent.h"
#include "Kismet/KismetMathLibrary.h"

AHumanMarineUnit::AHumanMarineUnit(){

    bHasHealthComp = true; //The units can take damage, so they have a health comp

    //Setting up the main meshes
    MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
    RootComponent = MainMesh;

    MeshToAttachTo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshToAttachTo"));
    //RootComponent = MeshToAttachTo;
    MeshToAttachTo->SetupAttachment(MainMesh);

    //Setting the main combat base variables to be different
    BaseDamage = 100.0f;

}

void AHumanMarineUnit::BeginPlay(){

    Super::BeginPlay();
    
    //UE_LOG(LogTemp, Warning, TEXT("Ref 017"));//Debug Line

    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Setting the spawn params to spawn the weapon no matter what

    WeaponComp = GetWorld()->SpawnActor<AWeaponComponent>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams); //Spawning the weapon if applicable	

    //If the weapon spawning succeded, we set the owner to this actor and attach the actors to each other
    if(WeaponComp){

        WeaponComp->SetOwner(this);
        WeaponComp-> AttachToComponent(MeshToAttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");

    }
    

}

//The attack function for the Marine unit
void AHumanMarineUnit::Attack(ABlanketActor* HitActor){

    Super::Attack(HitActor);

    //Rotating the actor to face the other actor
    RotateToVictim(HitActor);

    //Checking to see if the actor recently shot, and if so returns
    if(GetWorldTimerManager().IsTimerActive(FireDelay)){

        return;

    }

    //If the weapon component is valid, the weapon plays the firing effects
    if(WeaponComp){

       WeaponComp->Fire();

    }

    //This checks to see if the target has a health componenet that is valid and, if so, deals damage to it
    UBlanketHealthComponent* TargetHealthComp = Cast<UBlanketHealthComponent>(HitActor->GetComponentByClass(UBlanketHealthComponent::StaticClass()));

    if(TargetHealthComp){

        TargetHealthComp->TakeDamage(CalculateDamage());

    }

    GetWorldTimerManager().SetTimer(FireDelay, 1.0f, false, 100.0f/FireRate); //The fire delay timer function

}

//Rotating to face the victim
void AHumanMarineUnit::RotateToVictim(ABlanketActor* HitActor){

    FVector ActorLocation = GetActorLocation();
    FVector VictimLocation = HitActor->GetActorLocation();

    FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, VictimLocation);

    SetActorRotation(NewRotation);

    //ActorLocation.



}