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

	UFUNCTION(BlueprintCallable)
	bool IsSliding() const;

protected:

	UPROPERTY(Category = "Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
	float SlidingSpeed;

	UPROPERTY(Category = "Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
	float SlidingAccelerationControl;
	
	UPROPERTY(Category = "Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
    float MaxJumpRotation = 0.45f;
    
	UPROPERTY(Category = "Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
    float SlidingJumpBoost = 10000.f;

	// Natural sliding acceleration size (XY) 
	UPROPERTY(Category = "Character Movement: Sliding / Falling", BlueprintReadWrite, EditAnywhere)
    float slidingAcceleration = 15.f;

	UFUNCTION(BlueprintCallable)
	/**
	 * Detect if the floor is closer than the provided DistanceCheck parameter
	 *
	 * @param DistanceCheck How close the floor should be for the check to return true.
	 * @return Wether or not a floor was found within the given DistanceCheck constraint.
	 */
	bool IsFloorNear(float DistanceCheck = 0.05f);
	void PhysCustom(float deltaTime, int32 Iterations) override;
	bool CanAttemptJump() const override;
};
