// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_SpaceShip.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"


// Sets default values
ANH_SpaceShip::ANH_SpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	ShipMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("ShipMovementComponent");
}

// Called when the game starts or when spawned
void ANH_SpaceShip::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
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

}

float ANH_SpaceShip::GetLinearThrust(FVector Direction)
{
	if (bFlightAssist)
	{
		float S;
		float D;
		float A;
		S = FVector::DotProduct(Direction, Sphere->GetPhysicsLinearVelocity());
		D = S < 0 ? 1.0f : -1.0f;
		A = S == 0 ? 0.0f : D;
		return A;
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
	Sphere->SetPhysicsAngularVelocity(AngularAcceleration, true);
}

