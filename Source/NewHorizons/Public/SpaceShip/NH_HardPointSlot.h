// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "AbilitySystemComponent.h"
#include "Components/SceneComponent.h"
#include "NH_HardPointSlot.generated.h"


class ANH_HardPoint;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWHORIZONS_API UNH_HardPointSlot : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNH_HardPointSlot();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY()
	ANH_HardPoint* HardPoint;

public:

	UFUNCTION()
	ANH_HardPoint* GetHardPoint() const {return HardPoint; }

	UFUNCTION(BlueprintCallable)
	void AddHardPoint(TSubclassOf<ANH_HardPoint> NewHardPoint);

	UFUNCTION()
	void RemoveHardPoint();
};
