// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanMarineUnit.h"
#include "Components/SkeletalMeshComponent.h"
#include "BlanketActor.h"
#include "Infantry/Components/InfantryHealthComp.h"
#include "WeaponComponent.h"
#include "BlanketHealthComponent.h"

AHumanMarineUnit::AHumanMarineUnit(){

    bHasHealthComp = true;

    MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
    RootComponent = MainMesh;

    MeshToAttachTo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshToAttachTo"));
    //RootComponent = MeshToAttachTo;
    MeshToAttachTo->SetupAttachment(MainMesh);

    BaseDamage = 100.0f;

}

void AHumanMarineUnit::BeginPlay(){

    Super::BeginPlay();

    
    UE_LOG(LogTemp, Warning, TEXT("Ref 017"));

    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //Setting the spawn params to spawn the weapon no matter what

    WeaponComp = GetWorld()->SpawnActor<AWeaponComponent>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams); //Spawning the weapon if applicable	

    if(WeaponComp){

        WeaponComp->SetOwner(this);
        WeaponComp-> AttachToComponent(MeshToAttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");

    }
    

}

void AHumanMarineUnit::Attack(ABlanketActor* HitActor){

    Super::Attack(HitActor);

    if(GetWorldTimerManager().IsTimerActive(FireDelay)){

        return;

    }

    if(WeaponComp){

       WeaponComp->Fire();

    }

    UBlanketHealthComponent* TargetHealthComp = Cast<UBlanketHealthComponent>(HitActor->GetComponentByClass(UBlanketHealthComponent::StaticClass()));

    if(TargetHealthComp){

        TargetHealthComp->TakeDamage(CalculateDamage());

    }

    GetWorldTimerManager().SetTimer(FireDelay, 1.0f, false, 100.0f/FireRate);

}