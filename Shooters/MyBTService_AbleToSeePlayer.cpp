// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_AbleToSeePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "MyAIController.h"


UMyBTService_AbleToSeePlayer::UMyBTService_AbleToSeePlayer()
{
    NodeName = "Can ABle to See Player ";
}

void UMyBTService_AbleToSeePlayer::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp , NodeMemory , DeltaSeconds );
    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld() , 0);

    if(PlayerPawn && OwnerComp.GetAIOwner()){
        if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)){
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player") , PlayerPawn);
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation") , PlayerPawn->GetActorLocation());
                OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation") , PlayerPawn->GetActorLocation());
            }
        else{
                OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
            }
    }
   
    
}
