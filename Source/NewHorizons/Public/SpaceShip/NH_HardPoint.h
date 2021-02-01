// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "NH_HardPoint.generated.h"


class ANH_ShipWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWHORIZONS_API UNH_HardPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	UNH_HardPoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ANH_ShipWeapon* HardPoint;

public:

	UFUNCTION()
	ANH_ShipWeapon* GetHardPoint() const { return HardPoint; }

	UFUNCTION(BlueprintCallable)
	void AddHardPoint(TSubclassOf<ANH_ShipWeapon> NewHardPoint);

	UFUNCTION()
	void RemoveHardPoint();
};
