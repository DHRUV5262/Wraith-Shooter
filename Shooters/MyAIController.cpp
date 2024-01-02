// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "ShootingPlayer.h"

void AMyAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("MyActor initialized"));
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld() , 0);

    TArray<AActor*> PatrolPoints;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PatrolPoint"), PatrolPoints);


    // Do something with the patrol point actor
    FVector Location = PatrolPoints[0]->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("Patrol point is at location (%f, %f, %f)"), Location.X, Location.Y, Location.Z);
    if(AIBehavior){
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation") , GetPawn()->GetActorLocation());
        
        if(MyActor1){
            GetBlackboardComponent()->SetValueAsVector(TEXT("Patrol_Point1") , PatrolPoints[0]->GetActorLocation());
            
        }
        if(MyActor2){
            GetBlackboardComponent()->SetValueAsVector(TEXT("Patrol_Point2") , PatrolPoints[1]->GetActorLocation());
        }
        if(MyActor3){
            GetBlackboardComponent()->SetValueAsVector(TEXT("Patrol_Point3") , PatrolPoints[2]->GetActorLocation());
        }
    }    
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // if(LineOfSightTo(PlayerPawn)){
    //     //  MoveToActor(PlayerPawn , AccepatanceRadius);
    //     // SetFocus(PlayerPawn);
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation") , PlayerPawn->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation") , PlayerPawn->GetActorLocation());

    // }
    // else{
    //     ClearFocus(EAIFocusPriority::Gameplay);
    //     // StopMovement();
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    // }
}

bool AMyAIController::isDead() const
{
    AShootingPlayer* pawn = Cast<AShootingPlayer>(GetPawn());
    if(pawn){
        return pawn->isDead();
    } 
    return true;
}
