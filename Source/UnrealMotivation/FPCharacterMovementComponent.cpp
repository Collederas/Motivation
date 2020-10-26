// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
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

bool UFPCharacterMovementComponent::IsFloorNear(float DistanceCheck)
{
    FFindFloorResult FloorResult;
    FVector CapsLoc = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
    FindFloor(CapsLoc, FloorResult, false);
    return (FloorResult.FloorDist > 0 && FMath::IsNearlyZero(FloorResult.FloorDist, DistanceCheck));
}

void UFPCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations) 
{
    if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}

    FHitResult Hit(1.f);
    FCollisionQueryParams CollisionParams;

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 200), ECC_Visibility, CollisionParams);

    if (bHit) {
        FVector HitForward = Hit.GetActor()->GetActorForwardVector();
        DrawDebugLine(GetWorld(), Hit.Location, Hit.Location + HitForward * 100.0f, FColor::Emerald, false, 5.0f, 4.0f);

        float SlidingDirectionDetector = FVector::DotProduct(HitForward, FVector::UpVector);

        if (SlidingDirectionDetector > 0 && SlidingAccelerationMultiplier > 0 || SlidingDirectionDetector < 0 && SlidingAccelerationMultiplier < 0)
        {
            SlidingAccelerationMultiplier *= -1;
        }

        UE_LOG(LogTemp, Log, TEXT("SlidingDirectionDetector: %f"), SlidingDirectionDetector);
        UE_LOG(LogTemp, Log, TEXT("SlidingAccel: %f"), SlidingAccelerationMultiplier);

        Acceleration = HitForward * SlidingAccelerationMultiplier * 100.0f;

        Velocity = Acceleration * deltaTime;
        // UE_LOG(LogTemp, Log, TEXT("ACCEL AFTER CALC: %s"), *Velocity.ToString());

        const FVector Adjusted = Velocity * deltaTime;

        SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
    }
}
