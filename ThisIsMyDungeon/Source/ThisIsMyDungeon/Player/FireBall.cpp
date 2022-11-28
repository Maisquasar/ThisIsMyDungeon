// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBall.h"
#include "../DebugString.hpp"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "../Enemy/Enemy.h"

// Sets default values
AFireBall::AFireBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }   
    
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void AFireBall::BeginPlay()
{
	Super::BeginPlay();
    CurrentTime = TimeUntilDelete;
    //Getting Mesh.
    TArray<UStaticMeshComponent*> Components;
    GetComponents<UStaticMeshComponent>(Components);
    if (Components[0])
        Mesh = Components[0];
    else
        return;

    if (auto sphere = Mesh->GetChildComponent(0))
        SphereCollider = Cast<USphereComponent>(sphere);
    SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnCollision);
}

// Called every frame
void AFireBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (CurrentTime > 0)
    {
        CurrentTime -= DeltaTime;
    }
    else
    {
        Destroy();
    }

}

void AFireBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    if (auto Enemy = Cast<AEnemy>(OtherActor))
    {
        if (Enemy)
            Enemy->ApplyDamage(BaseDamage);
    }
}
