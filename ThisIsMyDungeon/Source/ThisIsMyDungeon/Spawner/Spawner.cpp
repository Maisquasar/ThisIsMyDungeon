// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "ThisIsMyDungeon/DungeonGameMode.h"
#include "../DebugString.hpp"
#include "../Player/PlayerCharacter.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//SpawnEnemy();
	
	/* for (int i = 0; i < WavesNumber; i++)
	{
		int32 fillArray[] = {i + 1};
		ArrayOfWaves.Append(fillArray, ARRAY_COUNT(fillArray));
	}*/
	

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	auto Player = Cast<APlayerCharacter>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	if (GM)
	{
		if (GM->counterEnemy <= 0)
		{
			if (Player) {
				if (GM->currentWave == GM->maxWaveCount && GM->counterEnemy <= 0)
				{
					Player->ShowVictory(true);
				}
			}
		}
	}
}

void ASpawner::SpawnEnemy()
{
	FTimerHandle Handle;

	for (int i = 0; i < spawnNumberEnemy; i++)
	{
		SpawnActor();
	}
	Actor++;

	if(numberOfSpawn > Actor)
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASpawner::SpawnEnemy, 7.f);
	}
	
}

void ASpawner::SpawnActor()
{
	
	ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->counterEnemy++;
	}
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
		
}

