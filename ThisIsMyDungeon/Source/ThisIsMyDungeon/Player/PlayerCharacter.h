// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../TrapPreview.h"
#include "../Trap.h"
#include "PlayerCharacter.generated.h"
#pragma once

#define Debug(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugError(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
#define DebugWarning(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(x), __VA_ARGS__));}

UCLASS()
class THISISMYDUNGEON_API APlayerCharacter : public ACharacter
{
private:
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
		FVector TreasureLoc;

	UPROPERTY(EditAnywhere)
		FVector SpawnLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UStaticMeshComponent* ProjectileStart;

	FTransform SpawnTransform;
	
	FTransform MeshRelativeTransform;

	bool RaycastFromCamera(FHitResult* RV_Hit);

	FHitResult hit;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void OnJump();

	void OnShoot();

	void OnTrapSetUp();

	void OnCancelTrap();

	void ApplyDamage(int Damage);

	void Respawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// Life
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		int MaxLife = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Life)
		int CurrentLife = 0;

	// Power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
		int MaxPower = 2000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Power)
		int CurrentPower = 0;

	UPROPERTY(EditAnywhere, Category = Power)
		int StartingPower = 800;

	// Projectiles
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AFireBall> ProjectileClass;

	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Trap")
		TSubclassOf<ATrap> trapTestPrefab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap")
		TSubclassOf<ATrap> currTrap;

	UPROPERTY(EditDefaultsOnly, Category = "Trap")
		TSubclassOf<ATrap> trapPreviewBlueprint;

	UPROPERTY(VisibleAnywhere, Category = "Trap")
		ATrap* trapPreviewInstance;

};
