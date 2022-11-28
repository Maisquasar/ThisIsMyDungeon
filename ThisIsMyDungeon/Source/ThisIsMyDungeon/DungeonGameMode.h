// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Spawner/Spawner.h"
#include "DungeonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THISISMYDUNGEON_API ADungeonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ADungeonGameMode();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere) 
		int currentWave = 0;

	UPROPERTY(EditAnywhere) 
		int waveState = 0;

	UPROPERTY(EditAnywhere)
		int treasureLife = 25;

	UPROPERTY(EditAnywhere)
		int counterEnemy = 0;

	UPROPERTY(EditAnywhere) 
		TArray<ASpawner*> Spawners;

public:

	void StartWaveGM();
	void TimeWaveGM();

};
