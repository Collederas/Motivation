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
	
protected:
	UPROPERTY(BlueprintReadWrite)
	int test;

	void PhysCustom(float deltaTime, int32 Iterations);
	void PhysFalling(float deltaTime, int32 Iterations);
};

