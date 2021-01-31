// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_HardPoint.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceShip/NH_ShipWeapon.h"
#include "SpaceShip/NH_SpaceShip.h"

UNH_HardPoint::UNH_HardPoint()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UNH_HardPoint::BeginPlay()
{
	Super::BeginPlay();
}

void UNH_HardPoint::AddHardPoint(TSubclassOf<ANH_ShipWeapon> NewHardPoint)
{
	HardPoint = GetWorld()->SpawnActor<ANH_ShipWeapon>(NewHardPoint, GetComponentLocation(), GetComponentRotation(), FActorSpawnParameters());
	HardPoint->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UNH_HardPoint::RemoveHardPoint()
{
	HardPoint->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	HardPoint->Destroy();
	HardPoint = nullptr;
}