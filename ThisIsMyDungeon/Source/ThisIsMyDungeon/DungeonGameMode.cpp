// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGameMode.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Kismet/GameplayStatics.h"


void ADungeonGameMode::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<ASpawner> ClassToFind;
	ClassToFind = ASpawner::StaticClass();
	TArray<AActor*> TempSpawner;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TempSpawner);

	for (int i = 0; i < TempSpawner.Num() - 1; i++)
	{
		Spawners.Add(Cast<ASpawner>(TempSpawner[i]));
	}
}

void ADungeonGameMode::StartWave()
{
	if(counterEnemy <= 0)
	{
		for (int i = 0; i <= Spawners.Num() - 1; i++)
		{
			for (int j = 0; j <= Spawners[i]->ArrayOfWaves.Num() - 1; j++)
			{
				if(Spawners[i]->ArrayOfWaves[j] == currentWave)
				{
					Spawners[i]->SpawnEnemy();
					counterEnemy += Spawners[i]->spawnNumberEnemy;
				}
			}
		}
	}
}



