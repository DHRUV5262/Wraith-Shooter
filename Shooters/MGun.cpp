// Fill out your copyright notice in the Description page of Project Settings.


#include "MGun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"


// Sets default values
AMGun::AMGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GUN"));
	gun->SetupAttachment(root);
}

// void AMGun::Trigger()
// {
// 	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash , gun , TEXT("MuzzleFlashSocket"));
// 	APawn* OwnerPawn = Cast<APawn>(GetOwner());
// 	if(OwnerPawn == nullptr)return;
// 	AController* Controller = OwnerPawn->GetController();
// 	if(Controller == nullptr)return ;
// 	FVector location ;
// 	FRotator rotation ;
// 	Controller->GetPlayerViewPoint(location , rotation);
// 	FVector End = location + rotation.Vector() * MaxRange; 	
// 	FHitResult Hit  ;
// 	bool S = GetWorld()->LineTraceSingleByChannel(Hit , location , End , ECollisionChannel::ECC_GameTraceChannel1);
// 	if(S)
// 	{		
// 		FVector ImpactDirection = -rotation.Vector();// for Showing particle effect in the direction of player
// 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld() , BulletCollide , Hit.Location , ImpactDirection.Rotation());
		
// 		if(Hit.GetActor() != nullptr){
			
// 			FVector Direction = Hit.ImpactNormal;
// 			TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();
// 			UGameplayStatics::ApplyPointDamage(Hit.GetActor(), Damage, ImpactDirection, Hit , GetOwner()->GetInstigatorController(), this, DamageType);
// 			FPointDamageEvent PointDamageEvent(Damage  , Hit , ImpactDirection , DamageType );
// 			Hit.GetActor()->TakeDamage(Damage , PointDamageEvent , Controller , this);
// 		}

// 			FPointDamageEvent PointDamageEvent(Damage, Hit, ImpactDirection);
// 			Hit.GetActor()->TakeDamage(Damage, PointDamageEvent, Controller, this);
// 		}
// 	}
// 	//for Camera 
// 	//DrawDebugCamera(GetWorld() , location , rotation , 90 ,2 ,FColor::Red , true);
// }


void AMGun::Trigger()
{
    
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, gun, TEXT("MuzzleFlashSocket"));
    UGameplayStatics::SpawnSoundAttached(MuzzleSound , gun ,TEXT("MuzzleFlashSocket") );
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn == nullptr) return;
    AController* Controller = OwnerPawn->GetController();
    if (Controller == nullptr) return;
    FVector location;
    FRotator rotation;
    Controller->GetPlayerViewPoint(location, rotation);
    FVector End = location + rotation.Vector() * MaxRange;
    FHitResult Hit;
    FCollisionQueryParams Params; // TO Ignore the collosion 
    Params.AddIgnoredActor(this); // ignore gun itself
    Params.AddIgnoredActor(GetOwner()); // ignore AiOwner 
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, location, End, ECollisionChannel::ECC_GameTraceChannel1 , Params);
   
    {

        FVector ImpactDirection = -rotation.Vector();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletCollide, Hit.Location, ImpactDirection.Rotation());
        UGameplayStatics::SpawnSoundAtLocation(GetWorld() , CollideSound , Hit.Location , ImpactDirection.Rotation() );


        if (Hit.GetActor() != nullptr)
        {
            FVector Direction = Hit.ImpactNormal;
            TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();
            UGameplayStatics::ApplyPointDamage(Hit.GetActor(), Damage, ImpactDirection, Hit, GetOwner()->GetInstigatorController(), this, DamageTypeClass);
        }
    }
}




void AMGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMGun::StartFire()
{
	Trigger();
	GetWorldTimerManager().SetTimer(TimerHandle_HandleRefired , this , &AMGun::Trigger , TimeBetweenShots , true);
}

void AMGun::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_HandleRefired);
}

// Called every frame
void AMGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




