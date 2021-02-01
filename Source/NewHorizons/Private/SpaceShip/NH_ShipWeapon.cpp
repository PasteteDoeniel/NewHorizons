// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip/NH_ShipWeapon.h"
#include "AbilitySystemComponent.h"

ANH_ShipWeapon::ANH_ShipWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	HardPointAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("HardPointAbilitySystemComponent"));
}

void ANH_ShipWeapon::Shoot()
{
	HardPointAbilitySystemComponent->TryActivateAbilityByClass(WeaponAbility);
}

void ANH_ShipWeapon::BeginPlay()
{
	Super::BeginPlay();

	HardPointAbilitySystemComponent->GiveAbility(WeaponAbility);	
}


