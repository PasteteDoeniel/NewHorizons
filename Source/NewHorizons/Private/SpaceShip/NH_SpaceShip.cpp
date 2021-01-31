// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_SpaceShip.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/SphereComponent.h"
#include "SpaceShip/NH_ShipWeapon.h"
#include "Components/ArrowComponent.h"
#include "AbilitySystemComponent.h"
#include "SpaceShip/NH_HardPoint.h"

ANH_SpaceShip::ANH_SpaceShip()
{
	
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;


	ShipAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ShipAbilitySystemComponent"));
}

void ANH_SpaceShip::BeginPlay()
{
	TArray<UNH_HardPoint> Components;
	GetComponents<UNH_HardPoint>(HardPointSlots);
	
	Super::BeginPlay();
}

void ANH_SpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Thrust();
}

// Called to bind functionality to input
void ANH_SpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Accelerate", this, &ANH_SpaceShip::ThrustForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ANH_SpaceShip::ThrustRight);
	PlayerInputComponent->BindAxis("Up", this, &ANH_SpaceShip::ThrustUp);

	PlayerInputComponent->BindAxis("Turn", this, &ANH_SpaceShip::Yaw);
	PlayerInputComponent->BindAxis("LookUp", this, &ANH_SpaceShip::Pitch);
	PlayerInputComponent->BindAxis("Roll", this, &ANH_SpaceShip::Roll);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ANH_SpaceShip::ShootPrimaryWeapons);
}

float ANH_SpaceShip::GetLinearThrust(FVector Direction)
{
	if (bFlightAssist)
	{
		float VelocityDotProduct;
		float OppositeThrust;
		float LinearThrust;
		VelocityDotProduct = FVector::DotProduct(Direction, Sphere->GetPhysicsLinearVelocity());
		OppositeThrust = VelocityDotProduct < 0 ? 1.0f : -1.0f;
		LinearThrust = VelocityDotProduct == 0 ? 0.0f : OppositeThrust;
		return LinearThrust;
	}
	else
	{
		return 0.0f;
	}
}

void ANH_SpaceShip::ThrustForward(float Value)
{
	ForwardAcceleration = Sphere->GetForwardVector() * (Value == 0.0f ? GetLinearThrust(Sphere->GetForwardVector()) : Value) * ThrustStrength;
}

void ANH_SpaceShip::ThrustRight(float Value)
{
	StrafeAcceleration = Sphere->GetRightVector() * (Value == 0.0f ? GetLinearThrust(Sphere->GetRightVector()) : Value) * ThrustStrength;
}

void ANH_SpaceShip::ThrustUp(float Value)
{
	UpAcceleration = Sphere->GetUpVector() * (Value == 0.0f ? GetLinearThrust(Sphere->GetUpVector()) : Value) * ThrustStrength;
}

void ANH_SpaceShip::Pitch(float Value)
{
	PitchAcceleration = Sphere->GetRightVector() * Value * TurnStrength;
}

void ANH_SpaceShip::Yaw(float Value)
{
	YawAcceleration = Sphere->GetUpVector() * Value * TurnStrength;
}

void ANH_SpaceShip::Roll(float Value)
{
	RollAcceleration = Sphere->GetForwardVector() * Value * TurnStrength;
}

void ANH_SpaceShip::Thrust()
{
	ThrusterAcceleration = ForwardAcceleration + StrafeAcceleration + UpAcceleration;
	Sphere->SetPhysicsLinearVelocity(ThrusterAcceleration, true);

	AngularAcceleration = PitchAcceleration + YawAcceleration + RollAcceleration;
	Sphere->SetPhysicsAngularVelocityInDegrees(AngularAcceleration, true);
}

//===========================================================

void ANH_SpaceShip::UnregisterHardpointAbility()
{
}

void ANH_SpaceShip::RegisterHardpointAbility(TSubclassOf<UGameplayAbility> GameplayAbility)
{
	if (HasAuthority())
	{
		ShipAbilitySystemComponent->GiveAbility(GameplayAbility);
	}
}

void ANH_SpaceShip::ShootPrimaryWeapons()
{
	for (auto& HardPointSlot : HardPointSlots)
	{
		if (ANH_ShipWeapon* HardPoint = HardPointSlot->GetHardPoint())
		{
			HardPoint->Shoot();
		}
	}
}

void ANH_SpaceShip::ShootSecondaryWeapons()
{
	
}

