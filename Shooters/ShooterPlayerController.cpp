// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    CrossHair = CreateWidget(this , Crosshair); // this will create a widget ui that we want to show 
    if(CrossHair != nullptr){
        CrossHair->AddToViewport(); // this will display our widget
    }
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus , bIsWinner);

    //CrossHair->RemoveFromViewport();
    if(bIsWinner)
    {
        UUserWidget* Winner = CreateWidget(this , WinnerScreen); // this will create a widget ui that we want to show 
        if(Winner != nullptr){
            Winner->AddToViewport(); // this will display our widget
        }
    }
    else
    {
        UUserWidget* loser = CreateWidget(this , LoserScreen); // this will create a widget ui that we want to show 
        if(loser != nullptr){
            loser->AddToViewport(); // this will display our widget
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer , this , &APlayerController::RestartLevel , RestartDelay);
}
