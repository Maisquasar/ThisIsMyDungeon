// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Trap.generated.h"

UCLASS()
class THISISMYDUNGEON_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canBePlacedInWorld = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* model;

	USceneComponent* root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* coll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Price)
		int Price = 100;

};
