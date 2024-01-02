// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "MyAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    
    APlayerController* Controller = Cast<APlayerController>(PawnKilled->GetController());
    if(Controller){
        GameHasEnded(false);
    }
    
    for(AMyAIController* contoller : TActorRange<AMyAIController>(GetWorld())){
        if(!contoller->isDead()){
            return;
        }
    }
    GameHasEnded(true);
}

void AKillEmAllGameMode::GameHasEnded(bool isPWinner)
{
    for(AController* contoller : TActorRange<AController>(GetWorld())){
        
        bool isWinner = contoller->IsPlayerController() == isPWinner ;
        contoller->GameHasEnded(contoller->GetPawn(), isWinner); // here contoller->GetPawn() is used to give more focus on player pawn rather than ai 
            // this will call player contoller to display the widgets accorind to result and restart the level
    }
}