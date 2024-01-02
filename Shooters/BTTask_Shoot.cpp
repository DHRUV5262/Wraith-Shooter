// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShootingPlayer.h"
#include "MyAIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = "Shoot" ;
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp , NodeMemory);

    if(OwnerComp.GetAIOwner()){
        AShootingPlayer* Player = Cast<AShootingPlayer>(OwnerComp.GetAIOwner()->GetPawn());
        if(Player){
            Player->ShotFired();
        }
    }

    return EBTNodeResult::Succeeded;
}