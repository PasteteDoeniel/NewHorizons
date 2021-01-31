// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_HardPointSlot.h"

#include "Kismet/GameplayStatics.h"
#include "SpaceShip/NH_HardPoint.h"
#include "SpaceShip/NH_SpaceShip.h"

UNH_HardPointSlot::UNH_HardPointSlot()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UNH_HardPointSlot::BeginPlay()
{
	Super::BeginPlay();
}

void UNH_HardPointSlot::AddHardPoint(TSubclassOf<ANH_HardPoint> NewHardPoint)
{
	HardPoint = GetWorld()->SpawnActor<ANH_HardPoint>(NewHardPoint, GetComponentLocation(), GetComponentRotation(), FActorSpawnParameters());
	HardPoint->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UNH_HardPointSlot::RemoveHardPoint()
{
	HardPoint->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	HardPoint->Destroy();
	HardPoint = nullptr;
}