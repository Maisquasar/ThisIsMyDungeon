// Fill out your copyright notice in the Description page of Project Settings.


#include "SeasawTrap.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "../DebugString.hpp"

ASeasawTrap::ASeasawTrap()
{
	seasawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("seasawMesh"));
	seasawMesh->SetupAttachment(Mesh);
}

void ASeasawTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 3;
	this->DescriptionText = "Deal a lot of damage to heroes who walk on them";
}

void ASeasawTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	seasawMesh->AddRelativeRotation(FQuat::MakeFromEuler(FVector(0, 720.f * DeltaTime, 0)));
	seasawMesh->SetRelativeLocation(FVector(sinf(GetWorld()->GetTimeSeconds() * 2.f) * 125.f, 0, 0));
}
