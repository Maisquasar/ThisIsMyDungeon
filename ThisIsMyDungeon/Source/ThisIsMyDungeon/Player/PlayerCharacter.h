// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../TrapPreview.h"
#include "../Trap.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THISISMYDUNGEON_API APlayerCharacter : public ACharacter
{
private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	class UStaticMeshComponent* ProjectileStart;

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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

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
