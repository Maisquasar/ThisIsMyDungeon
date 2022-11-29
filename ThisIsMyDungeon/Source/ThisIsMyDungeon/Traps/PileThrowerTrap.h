// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GenericTrap.h"
#include "PileThrowerTrap.generated.h"

/**
 * 
 */
UCLASS()
class THISISMYDUNGEON_API APileThrowerTrap : public AGenericTrap
{
	GENERATED_BODY()
public:
	APileThrowerTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
