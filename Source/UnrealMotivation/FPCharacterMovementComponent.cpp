// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UFPCharacterMovementComponent::UFPCharacterMovementComponent()
{
    OriginalAirControl = AirControl;
}

void UFPCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
    Super::PhysWalking(deltaTime, Iterations);
}

void UFPCharacterMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
    Super::PhysFalling(deltaTime, Iterations);
    if (IsFloorNear())
    {
        AirControl = SlidingAirControl;
    }
}

bool UFPCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
    if (CharacterOwner && CharacterOwner->CanJump())
    {
        // Don't jump if we can't move up/down.
        if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
        {
            if (IsFloorNear())
            {
                Velocity = CharacterOwner->GetActorForwardVector() * ForwardJumpMultiplier;
            }

            Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
            SetMovementMode(MOVE_Falling);
            return true;
        }
    }

    return false;
}

bool UFPCharacterMovementComponent::IsFloorNear(float DistanceCheck)
{
    FFindFloorResult FloorResult;
    FVector CapsLoc = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
    FindFloor(CapsLoc, FloorResult, false);
    return (FloorResult.FloorDist > 0 && FMath::IsNearlyZero(FloorResult.FloorDist, DistanceCheck));
}