// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootersGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API AKillEmAllGameMode : public AShootersGameModeBase
{
	GENERATED_BODY()
	public:
		virtual void PawnKilled(APawn* PawnKilled) override;
	
	private:
		void GameHasEnded(bool isPWinner); 
};
