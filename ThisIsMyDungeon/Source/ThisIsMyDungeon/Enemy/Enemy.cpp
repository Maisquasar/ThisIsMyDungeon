// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "ThisIsMyDungeon/DungeonGameMode.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../DebugString.hpp"
#include "../Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn());
	MaxSpeed = this->GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UNavigationSystemV1::TestPathSync()
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::ApplyDamage(int Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		ADungeonGameMode* GM = Cast<ADungeonGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
			GM->counterEnemy--;
		Player->AddPower(10);
		Destroy();
	}
}

FName AEnemy::GetClosestSocket(FVector pos)
{
	float distance = FLT_MAX;
	FName currentSkel;
	for (auto skelName : GetMesh()->GetAllSocketNames())
	{
		auto skel = GetMesh()->GetSocketLocation(skelName);
		float currentDistance = FVector::Distance(pos, skel);
		if (distance > currentDistance)
		{
			distance = currentDistance;
			currentSkel = skelName;
		}
	}
	return currentSkel;
}

