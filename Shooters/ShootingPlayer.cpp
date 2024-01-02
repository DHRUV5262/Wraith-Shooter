// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingPlayer.h"
#include "Components/CapsuleComponent.h"
#include "ShootersGameModeBase.h"


// Sets default values
AShootingPlayer::AShootingPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AShootingPlayer::isDead() const
{
    return Health <= 0;
}

float AShootingPlayer::GetHealthPercent() const
{
    return Health / MaxHealth;
}

// Called when the game starts or when spawned
void AShootingPlayer::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AMGun>(GunClass);
	//GetMesh()->HideBoneByName(TEXT("weapon_r") , EPhysBodyOp::PBO_None );
	Gun->AttachToComponent(GetMesh() , FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun ->SetActorHiddenInGame(true);
	Gun->SetOwner(this);

	//Launcherclass = GetWorld()->SpawnActor<AGrenadeLauncher>(Laucher);
	//Launcherclass->AttachToComponent(GetMesh() , FAttachmentTransformRules::KeepRelativeTransform);
	//Launcherclass->SetOwner(this);
	//Launcherclass->SetActorHiddenInGame(true);

	Health = MaxHealth ;
}	

// Called every frame
void AShootingPlayer::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void AShootingPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward") , this , &AShootingPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight") , this , &AShootingPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp") , this , &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate") , this , &AShootingPlayer::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate") , this , &AShootingPlayer::LookRightRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight") , this , &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump") , EInputEvent::IE_Pressed , this , &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire") , EInputEvent::IE_Pressed , this , &AShootingPlayer::StartShooting);
	PlayerInputComponent->BindAction(TEXT("Fire") , EInputEvent::IE_Released , this , &AShootingPlayer::StopShooting);
	//PlayerInputComponent->BindAxis("MouseWheel", this, &AShootingPlayer::ScrollInput);
	
}


float AShootingPlayer::TakeDamage(float DamageAmoint , struct FDamageEvent const &FDamageEvent , class AController *EventInstigator, AActor *DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmoint ,FDamageEvent ,EventInstigator , DamageCauser);
	if(Health > 0){
		Health -= DamageApplied ;
	}
	UE_LOG(LogTemp, Display, TEXT("hEALTH = %f"), Health);
	if(isDead()){
		AShootersGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShootersGameModeBase>();
		if(GameMode){
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied ;
}

void AShootingPlayer::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AShootingPlayer::LookUpRate(float value)
{
	AddControllerPitchInput(value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingPlayer::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AShootingPlayer::LookRightRate(float value)
{
	AddControllerYawInput(value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShootingPlayer::ShotFired()
{
	Gun->Trigger();
}

// void AShootingPlayer::ScrollInput(float scroll)
// {

// 	if(scroll > 0){
// 		currentweaponIndex = (currentweaponIndex + 1) % 2 ;
// 	}
// 	else if (scroll < 0)
//     {
//         // Scroll down, decrement weapon index
//         currentweaponIndex  = (currentweaponIndex  - 1 + 2) % 2;
//     }

// 	SwitchWeapons(currentweaponIndex);
// }

// void AShootingPlayer::SwitchWeapons(int32 NewWeaponIndex)
// {
// 	if(NewWeaponIndex == 0){
// 		Launcherclass->SetActorHiddenInGame(true);
// 		Gun->SetActorHiddenInGame(false);
// 	}
// 	else if(NewWeaponIndex == 1){
// 		Gun->SetActorHiddenInGame(true);
// 		Launcherclass->SetActorHiddenInGame(false);
// ;
// 	}
// 	currentweaponIndex = NewWeaponIndex ;
// }

void AShootingPlayer::StartShooting()
{
	Gun->StartFire();
}

void AShootingPlayer::StopShooting()
{
	Gun->StopFire();
}
