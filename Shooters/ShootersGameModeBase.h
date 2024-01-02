// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootersGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API AShootersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
		virtual void PawnKilled(APawn* Pawn);
	
};
