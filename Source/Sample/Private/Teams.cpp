// Fill out your copyright notice in the Description page of Project Settings.


#include "Teams.h"

Teams::Teams()
{
}

Teams::~Teams()
{
}

bool Teams::IsInTeam(Teams* TeamComponent){

    if(TeamComponent->PlayerNumber == PlayerNumber){

        return true;

    }

    for(int32 i = 0; i < TeamNumbers.Num(); i++){

        if(TeamNumbers.Last(i) == TeamComponent->PlayerNumber){

            return true;

        }

    }

    return false;

}
