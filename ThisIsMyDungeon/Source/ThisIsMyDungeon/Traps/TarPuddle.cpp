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
}

void ATarPuddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


