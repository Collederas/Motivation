// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UFPCharacterMovementComponent::UFPCharacterMovementComponent()
{
    OriginalAirControl = AirControl;
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

void UFPCharacterMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{
    if (IsFloorNear())
    {
        AirControl = SlidingAirControl;
    }
    Super::PhysFalling(deltaTime, Iterations);
}

void UFPCharacterMovementComponent::ProcessLanded(const FHitResult &Hit, float remainingTime, int32 Iterations)
{
    Super::ProcessLanded(Hit, remainingTime, Iterations);
    AirControl = OriginalAirControl;
}

bool UFPCharacterMovementComponent::IsFloorNear(float DistanceCheck)
{
    FFindFloorResult FloorResult;
    FVector CapsLoc = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
    FindFloor(CapsLoc, FloorResult, false);
    return (FloorResult.FloorDist > 0 && FMath::IsNearlyZero(FloorResult.FloorDist, DistanceCheck));
}

FVector UFPCharacterMovementComponent::HandleSlopeBoosting(const FVector &SlideResult, const FVector &Delta, const float Time, const FVector &Normal, const FHitResult &Hit) const
{
    // Do not cancel out the whole Z component. I set it to 0.5f the original value.

    FVector Result = SlideResult;

    if (Result.Z > 0.f)
    {
        // Don't move any higher than we originally intended.
        const float ZLimit = Delta.Z * Time;

        if (Result.Z - ZLimit > KINDA_SMALL_NUMBER)
        {
            if (ZLimit > 0.f)
            {
                // Rescale the entire vector (not just the Z component) otherwise we change the direction and likely head right back into the impact.
                const float UpPercent = ZLimit / Result.Z;
                Result *= UpPercent;
                UE_LOG(LogTemp, Warning, TEXT("UpPercent, %f"), UpPercent);
            }
            else
            {
                // We were heading down but were going to deflect upwards. Just make the deflection horizontal.
                Result = FVector::ZeroVector;
            }
            UE_LOG(LogTemp, Warning, TEXT("Still going in"));

            // Make remaining portion of original result horizontal and parallel to impact normal.
            const FVector Remainder = (SlideResult - Result) * FVector(1.f, 1.f, 0.5f);
            const FVector NormalXY = Normal.GetSafeNormal2D();
            const FVector Adjust = Super::ComputeSlideVector(Remainder, 1.f, NormalXY, Hit);
            Result += Adjust;
        }
    }

    return Result;
}
