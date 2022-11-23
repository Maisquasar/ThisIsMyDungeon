// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEnemy* Chr = Cast<AEnemy>(InPawn);
	if (Chr != nullptr && Chr->TreeAsset != nullptr)
	{
		BBC->InitializeBlackboard(*Chr->TreeAsset->BlackboardAsset);
		GoToLocationId = BBC->GetKeyID("GoToLocation");
		BTC->StartTree(*Chr->TreeAsset);
	}

	TArray<AActor*> treasure;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Treasure"), treasure);
	BBC->SetValueAsVector("GoToLocation", treasure[0]->GetActorLocation());
	
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	

}