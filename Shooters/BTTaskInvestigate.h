// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskInvestigate.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API UBTTaskInvestigate : public UBTTaskNode
{
	GENERATED_BODY()
	
	public:
		UBTTaskInvestigate();
	
	protected:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
