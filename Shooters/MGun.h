// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGun.generated.h"

UCLASS()
class SHOOTERS_API AMGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMGun();

	void Trigger();

	void StartFire();
	void StopFire();
	void ShotFired();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent *root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *gun;

	UPROPERTY(EditAnywhere)
	UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound ;

	UPROPERTY(EditAnywhere)
	USoundBase* CollideSound ;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	UParticleSystem *BulletCollide;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	FTimerHandle TimerHandle_HandleRefired;

	float TimeBetweenShots = 0.1;

	
	
};
