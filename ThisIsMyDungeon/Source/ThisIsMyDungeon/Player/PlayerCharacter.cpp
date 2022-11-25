// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "../DebugString.hpp"
#include "DrawDebugHelpers.h"
#include "FireBall.h"
#include "NavigationData.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AddLocalOffset(FVector(0, 0, 100));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	ProjectileStart = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto children = GetMesh()->GetChildComponent(0);
	if (Cast<UStaticMeshComponent>(children))
		ProjectileStart = Cast<UStaticMeshComponent>(children);
	CurrentLife = MaxLife;
	CurrentPower = StartingPower;
	MeshRelativeTransform = GetMesh()->GetRelativeTransform();
	SpawnTransform = GetActorTransform();

	hit = FHitResult(ForceInit);
}

void APlayerCharacter::OnJump()
{
}


void APlayerCharacter::OnShoot()
{
	if (!ProjectileStart || !ProjectileClass)
		return;

	// Raycast Point to find hit point.
	FHitResult Hit;

	RaycastFromCamera(&Hit, 600000);
	if (Hit.bBlockingHit) {
		GetWorld()->SpawnActor<AFireBall>(ProjectileClass, ProjectileStart->GetComponentLocation(), (Hit.Location - ProjectileStart->GetComponentLocation()).ToOrientationRotator());
	}
	else
		GetWorld()->SpawnActor<AFireBall>(ProjectileClass, ProjectileStart->GetComponentLocation(), FollowCamera->GetForwardVector().ToOrientationRotator());
}

void APlayerCharacter::ApplyDamage(int Damage)
{
	CurrentLife -= Damage;
	if (CurrentLife <= 0)
	{
		CurrentLife = 0;

		// Enable Ragdoll
		UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
		DisableInput(Cast<APlayerController>(GetController()));
		GetMesh()->SetAllBodiesSimulatePhysics(true);

		FTimerHandle _;
		GetWorldTimerManager().SetTimer(_, this, &APlayerCharacter::Respawn, 5.f, false);
	}
}

void APlayerCharacter::Respawn()
{
	// Disable Ragdoll
	EnableInput(Cast<APlayerController>(GetController()));
	GetMesh()->SetAllBodiesSimulatePhysics(false);
	GetMesh()->AttachTo(GetCapsuleComponent());
	GetMesh()->SetRelativeLocationAndRotation(MeshRelativeTransform.GetLocation(), MeshRelativeTransform.GetRotation());
	this->SetActorTransform(SpawnTransform);
	CurrentLife = MaxLife;
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currTrap)
	{
		if (trapPreviewInstance)
		{
			
			RaycastFromCamera(&hit);
			FVector snappedPos = hit.Location;
			float wholePart;

			if (fabsf(hit.Normal.X) < 0.9f)
			{
				snappedPos.X -= modff(snappedPos.X / 100.f, &wholePart) * 100.f;
				snappedPos.X += hit.Location.X > 0 ? 50 : -50;
			}
			if (fabsf(hit.Normal.Y) < 0.9f)
			{
				snappedPos.Y -= modff(snappedPos.Y / 100.f, &wholePart) * 100.f;
				snappedPos.Y += hit.Location.Y > 0 ? 50 : -50;
			}
			if (fabsf(hit.Normal.Z) < 0.9f)
			{
				snappedPos.Z -= modff(snappedPos.Z / 100.f, &wholePart) * 100.f;
				snappedPos.Z += hit.Location.Z > 0 ? 50 : -50;
			}

			// TO CHANGE
			trapPreviewInstance->SetActorLocation(snappedPos + hit.Normal * trapPreviewInstance->model->GetComponentScale().Z * 50);
			FRotator rot = FRotationMatrix::MakeFromZ(hit.Normal).Rotator();
			trapPreviewInstance->SetActorRotation(rot);
		}
	}
	this->SetActorRotation(UKismetMathLibrary::RInterpTo(GetActorRotation(), FRotator::MakeFromEuler(FVector(GetActorRotation().Euler().X, GetActorRotation().Euler().Y, FollowCamera->GetComponentRotation().Euler().Z)), DeltaTime, 5.f));
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::OnShoot);

	PlayerInputComponent->BindAction("SetUpTrap", IE_Pressed,this, &APlayerCharacter::OnTrapSetUp);
	PlayerInputComponent->BindAction("CancelTrap", IE_Pressed, this, &APlayerCharacter::OnCancelTrap);

	{
		FInputActionBinding ActionBinding("ChooseTrap1", IE_Pressed);
		ActionBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]
			{
				if (currTrap) return;
				currTrap = trapTestPrefab;
				trapPreviewInstance = Cast<ATrap>(GetWorld()->SpawnActor(trapPreviewBlueprint));
				UStaticMesh* mesh = trapTestPrefab.GetDefaultObject()->model->GetStaticMesh();
				
				if (mesh)
				{
					trapPreviewInstance->model->SetStaticMesh(mesh);
					Debug("mesh is set");
				}
				
				Debug("Choose trap 1");
			});
		PlayerInputComponent->AddActionBinding(ActionBinding);
	}



	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

}

bool APlayerCharacter::RaycastFromCamera(FHitResult* RV_Hit, float MaxDistance)
{
	if (Controller == NULL) { return false; }

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = true;

	RV_TraceParams.AddIgnoredActor(this);

	FVector pos;
	FVector dir;
	FVector2D screenSize;
	GetWorld()->GetGameViewport()->GetViewportSize(screenSize);
	screenSize = screenSize / 2;
	Cast<APlayerController>(this->GetController())->DeprojectScreenPositionToWorld(screenSize.X, screenSize.Y, pos, dir);

	// Raycast Point to find hit point.
	FHitResult Hit;
	auto StartLocation = pos;
	auto EndLocation = StartLocation + (FollowCamera->GetForwardVector() * MaxDistance);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red);
	return GetWorld()->LineTraceSingleByChannel(*RV_Hit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, RV_TraceParams);
}

void APlayerCharacter::OnTrapSetUp()
{
	FVector normal = hit.Normal;
	//Debug("%.2f, %.2f, %.2f", normal.X, normal.Y, normal.Z);
	if (!trapPreviewInstance || CurrentPower < trapPreviewInstance->Price) return;
	if (!trapPreviewInstance->canBePlacedInWorld) return;

	if(normal == FVector(0, 0, 0)) 
	{
		// raycast hit nothing
		Debug("None");

		return;
	}

	CurrentPower -= trapPreviewInstance->Price;
	if (normal.Z > 0.9f)
	{
		// raycast hit the ground
		Debug("Ground");
		GetWorld()->SpawnActor<ATrap>(currTrap, trapPreviewInstance->GetActorLocation(), trapPreviewInstance->GetActorRotation());
		trapPreviewInstance->Destroy();
		currTrap = 0;
	}
	else
	{
		// raycast hit a wall
		Debug("Wall");
		GetWorld()->SpawnActor<ATrap>(currTrap, trapPreviewInstance->GetActorLocation(), trapPreviewInstance->GetActorRotation());
		trapPreviewInstance->Destroy();
		currTrap = 0;
		return;
	}
	
}

void APlayerCharacter::OnCancelTrap()
{
	if (!currTrap) return;
	trapPreviewInstance->Destroy();
	currTrap = 0;
}

