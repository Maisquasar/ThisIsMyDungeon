// Fill out your copyright notice in the Description page of Project Settings.


#include "PileThrowerTrap.h"
#include "Components/StaticMeshComponent.h"
#include "../DebugString.hpp"

APileThrowerTrap::APileThrowerTrap()
{

}

void APileThrowerTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 4;
	this->DescriptionText = "Throw pile at your enemies for a large area of damage";
}

void APileThrowerTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
