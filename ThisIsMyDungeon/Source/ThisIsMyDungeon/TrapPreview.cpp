// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapPreview.h"

// Sets default values
ATrapPreview::ATrapPreview()
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



// Called every frame
void ATrapPreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

