// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbility.h"
#include "GameFramework/Actor.h"
#include "NH_HardPoint.generated.h"

class UAbilitySystemComponent;
UCLASS()
class NEWHORIZONS_API ANH_HardPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANH_HardPoint();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayAbility> WeaponAbility;

	UFUNCTION()
	void Shoot(UAbilitySystemComponent* AbilitySystemComponent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
