// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskInvestigate.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"


UBTTaskInvestigate::UBTTaskInvestigate()
{
}

EBTNodeResult::Type UBTTaskInvestigate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    USkeletalMeshComponent* MeshComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<USkeletalMeshComponent>();
    if (!MeshComponent)
    {
        return EBTNodeResult::Failed;
    }

    UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
    if (!AnimInstance)
    {
        return EBTNodeResult::Failed;
    }

    UAnimMontage* MontageToPlay = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/Path/To/Your/Montage.AnimMontage"), nullptr, LOAD_None, nullptr);
    if (!MontageToPlay)
    {
        return EBTNodeResult::Failed;
    }

    // Play the animation montage
    AnimInstance->Montage_Play(MontageToPlay);

    // Wait for 5 seconds while the animation plays
    float StartTime = OwnerComp.GetWorld()->GetTimeSeconds();
    float EndTime = StartTime + 5.0f;

    while (OwnerComp.GetWorld()->GetTimeSeconds() < EndTime)
    {
        // Wait for the animation to finish playing
    }

    // Stop the animation montage
    AnimInstance->Montage_Stop(0.2f, MontageToPlay);

    return EBTNodeResult::Succeeded;
}