// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericTrap.h"
#include "Components/BoxComponent.h"
#include "DebugString.hpp"
#include "Player/PlayerCharacter.h"

// Sets default values
AGenericTrap::AGenericTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGenericTrap::BeginPlay()
{
	Super::BeginPlay();

	//Getting Mesh.
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if (Components[0])
		Mesh = Components[0];
	else
		return;

	DefaultMaterial = Mesh->GetMaterial(0);
	Mesh->SetMaterial(0, InvalidPreviewMaterial);
	Player = Cast<APlayerCharacter>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
}

// Called every frame
void AGenericTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Placed) {
		CanBePlaced = !IsOverlappingSomeone() && Player->CurrentPower >= Cost;
		if (CanBePlaced)
		{
			Mesh->SetMaterial(0, ValidPreviewMaterial);
		}
		else
		{
			Mesh->SetMaterial(0, InvalidPreviewMaterial);
		}
	}
}

void AGenericTrap::SetUp()
{
	Placed = true;
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetMaterial(0, DefaultMaterial);
}
