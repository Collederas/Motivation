// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPCharacterMovementComponent.generated.h"

/**
 * Custom Movement Component that sligthly tweaks the original to implement hopefully more engaging sliding gameplay.
 */
UCLASS()
class UNREALMOTIVATION_API UFPCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	UFPCharacterMovementComponent();

public:
	bool DoJump(bool bReplayingMoves) override;

protected:
	/** What boost to give to the standard Jump velocity when jumping from a slope. */
	UPROPERTY(Category="Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
	float ForwardJumpMultiplier;

	/** Determines what AirControl value to use when sliding on slopes. */
	UPROPERTY(Category="Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
	float SlidingAirControl;

	UFUNCTION(BlueprintCallable)
	/**
	 * Detect if the floor is closer than the provided DistanceCheck parameter
	 *
	 * @param DistanceCheck How close the floor should be for the check to return true.
	 * @return Wether or not a floor was found within the given DistanceCheck constraint.
	 */
	bool IsFloorNear(float DistanceCheck = 0.05f);

private:
	float OriginalAirControl;
};

