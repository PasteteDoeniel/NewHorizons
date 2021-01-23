// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NH_SpaceShip.generated.h"

class UFloatingPawnMovement;
class UInputComponent;
class USphereComponent;
class UArrowComponent;

UCLASS(config = Game)
class NEWHORIZONS_API ANH_SpaceShip : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* ShipMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

public:
	// Sets default values for this pawn's properties
	ANH_SpaceShip();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ThrustStrength = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TurnStrength = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bFlightAssist = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetLinearThrust(FVector Direction);

	void ThrustForward(float Value);
	void ThrustRight(float Value);
	void ThrustUp(float Value);

	void Pitch(float Value);
	void Yaw(float Value);
	void Roll(float Value);

	void Thrust();

	FVector ForwardAcceleration;
	FVector StrafeAcceleration;
	FVector UpAcceleration;

	FVector PitchAcceleration;
	FVector YawAcceleration;
	FVector RollAcceleration;

	UPROPERTY()
	FVector AngularAcceleration;

	UPROPERTY()
	FVector ThrusterAcceleration;

	UFUNCTION(BlueprintPure)
	FVector GetThrusterAcceleration() const { return ThrusterAcceleration;	}
};
