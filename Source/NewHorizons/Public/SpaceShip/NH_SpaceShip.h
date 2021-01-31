// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"

#include "NH_SpaceShip.generated.h"

class UGameplayAbility;
class UFloatingPawnMovement;
class UInputComponent;
class USphereComponent;
class UArrowComponent;
class UNH_HardPointSlot;

UCLASS(config = Game)
class NEWHORIZONS_API ANH_SpaceShip : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override {return ShipAbilitySystemComponent;}

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* ShipMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* ShipAbilitySystemComponent;

public:
	ANH_SpaceShip();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ThrustStrength = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TurnStrength = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bFlightAssist = true;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//===============ShipMovement================================
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

//===========================================================

	UFUNCTION()
	void UnregisterHardpointAbility();

	UFUNCTION()
	void RegisterHardpointAbility(TSubclassOf<UGameplayAbility> GameplayAbility);

	UFUNCTION()
	void ShootPrimaryWeapons();

	UFUNCTION()
    void ShootSecondaryWeapons();

protected:
	UPROPERTY()
	TArray<UNH_HardPointSlot*> HardPointSlots;

public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	TArray<UNH_HardPointSlot*> GetHardPointSlots() const {return HardPointSlots; }
};
