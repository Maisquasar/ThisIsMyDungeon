// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTrap.h"
#include "Components/StaticMeshComponent.h"
#include "../DebugString.hpp"

ABoxTrap::ABoxTrap()
{

}

void ABoxTrap::BeginPlay()
{
	Super::BeginPlay();
	Index = 1;
}

void ABoxTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
