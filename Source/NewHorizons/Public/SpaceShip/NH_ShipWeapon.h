// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Actor.h"
#include "NH_ShipWeapon.generated.h"

class UAbilitySystemComponent;
UCLASS()
class NEWHORIZONS_API ANH_ShipWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANH_ShipWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* HardPointAbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayAbility> WeaponAbility;

	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override {return HardPointAbilitySystemComponent;};

	UFUNCTION()
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
