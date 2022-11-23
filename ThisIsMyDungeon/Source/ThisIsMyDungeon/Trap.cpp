// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	root->SetupAttachment(RootComponent);

	model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	model->SetupAttachment(root);

	coll = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	coll->SetupAttachment(model);
	


}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

