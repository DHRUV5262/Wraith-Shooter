// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_AbleToSeePlayer.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API UMyBTService_AbleToSeePlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public: 
	UMyBTService_AbleToSeePlayer();

protected:
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
