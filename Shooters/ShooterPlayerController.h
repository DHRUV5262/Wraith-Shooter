// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
		virtual void GameHasEnded(class AActor *EndGameFocus = nullptr , bool bIsWinner = false) override ;

	private:
		UPROPERTY(EditAnywhere)
		float RestartDelay = 4 ;

		UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoserScreen ;

		UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinnerScreen ;

		UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> Crosshair ;

		FTimerHandle RestartTimer ;

		UUserWidget* CrossHair ;


};
