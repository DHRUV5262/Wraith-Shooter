// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGun.h"
#include "ShootingPlayer.generated.h"


UCLASS()
class SHOOTERS_API AShootingPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShootingPlayer();

	UFUNCTION(BlueprintPure)
	bool isDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmoint , struct FDamageEvent const &FDamageEvent , class AController *EventInstigator, AActor *DamageCauser) override ;
	
	void ShotFired();
private:
	void MoveForward(float value);
	void LookUpRate(float value);
	void MoveRight(float value);
	void LookRightRate(float value);

	UPROPERTY(EditAnywhere)
	float RotationRate = 10 ;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health ;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMGun> GunClass ;

	UPROPERTY()
	AMGun* Gun ;

	//UPROPERTY()
	//class AGrenadeLauncher* Launcherclass;

	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class AGrenadeLauncher> Laucher ;

	int32 currentweaponIndex = 0 ;

	void ScrollInput(float scroll) ;

	void SwitchWeapons(int32 NewWeaponIndex);

	void StartShooting();
	void StopShooting();

};
