// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ABlanketActor;
class ASamplePlayerController;
class SAMPLE_API Teams
{
public:
	Teams();
	~Teams();

	ABlanketActor* OwningActor;

	int32 PlayerNumber;

	TArray<int32> TeamNumbers;

	bool IsInTeam(Teams* TeamComponent);

	ASamplePlayerController* TeamController;
};
