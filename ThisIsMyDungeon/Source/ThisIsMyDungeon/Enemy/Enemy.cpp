// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "ThisIsMyDungeon/DungeonGameMode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Health = 200;
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UNavigationSystemV1::TestPathSync()
	ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	if (Health <= 0)
	{
		Destroy();
		GM->counterEnemy--;
	}


}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

