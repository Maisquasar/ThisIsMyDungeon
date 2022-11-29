// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

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
		TArray<FVector> SpawnLoc;

	UPROPERTY(EditAnywhere)
		FVector PlayerSpawn;

	UPROPERTY(EditAnywhere)
		class AGenericTrap* lastTrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UStaticMeshComponent* ProjectileStart;

	FTransform SpawnTransform;
	
	FTransform MeshRelativeTransform;

	bool RaycastFromCamera(FHitResult* RV_Hit, float MaxDistance = 1000.f);

	bool TrapHidden = false;

	FHitResult hit;

	float _currentTime = 0;

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

	void DisableTrap(bool);

	void Respawn();

	void OnTrap1();
	void OnTrap2();
	void OnTrap3();
	void OnTrap4();

	void SelectTrap(int index);

	void CheckPath();

	void StartWave();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	void AddPower(int add);

	UFUNCTION(BlueprintCallable)
		int GetCurrentTrapIndex();

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
		int CurrentPower = 0;

	UPROPERTY(EditAnywhere, Category = Power)
		int StartingPower = 800;

	// Projectiles
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AFireBall> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
		class AGenericTrap* CurrentTrap;

	UPROPERTY(EditDefaultsOnly, Category = "Trap")
		TArray<TSubclassOf<class AGenericTrap>> TrapsBlueprint;
};
