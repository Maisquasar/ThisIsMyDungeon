// Fill out your copyright notice in the Description page of Project Settings.


#include "TarPuddle.h"
#include "../DebugString.hpp"

ATarPuddle::ATarPuddle()
{

}

void ATarPuddle::BeginPlay()
{
	Super::BeginPlay();
	Index = 2;
	this->DescriptionText = "Slow down heros and useful for traps to make more damage.";
}

void ATarPuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


