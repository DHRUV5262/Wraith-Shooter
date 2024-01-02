// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERS_API AMyAIController : public AAIController
{
	GENERATED_BODY()

	protected:
		virtual void BeginPlay() override;
	
	public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	bool isDead() const ;

	private:

		APawn* PlayerPawn ;
		float AccepatanceRadius = 200;

		UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior ;

		class AActor* MyActor1 ;
		class AActor* MyActor2 ;
		class AActor* MyActor3 ;

};

