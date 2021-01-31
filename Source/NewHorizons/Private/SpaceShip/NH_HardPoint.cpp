// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_HardPoint.h"

#include "SpaceShip/NH_HardPointSlot.h"

ANH_HardPoint::ANH_HardPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	HardPointAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("HardPointAbilitySystemComponent"));
}

void ANH_HardPoint::Shoot()
{
	HardPointAbilitySystemComponent->TryActivateAbilityByClass(WeaponAbility);
}

void ANH_HardPoint::BeginPlay()
{
	Super::BeginPlay();

	HardPointAbilitySystemComponent->GiveAbility(WeaponAbility);	
}


