// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPCharacterMovementComponent.generated.h"

/** Custom MovementMode options. */
UENUM(BlueprintType)
enum ECustomMovementMode
{
	/** Sliding down a non-walkable surface. */
	MOVE_Sliding	UMETA(DisplayName="Sliding")
};

/**
 * Custom Movement Component that implements more MovementMode options.
 */
UCLASS()
class UNREALMOTIVATION_API UFPCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	bool DoJump(bool bReplayingMoves) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SlidingFloorDistanceErrorTolerance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ForwardJumpMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SlidingJumpAirControl;
};

