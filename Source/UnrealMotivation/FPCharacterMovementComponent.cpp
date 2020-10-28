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
    UE_LOG(LogTemp, Log, TEXT("CanJump: %d"), CharacterOwner->CanJump());
    if (CharacterOwner && CharacterOwner->CanJump())
    {
        // Don't jump if we can't move up/down.
        if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
        {
            UE_LOG(LogTemp, Log, TEXT("Jumping with %f Z Velocity"), Velocity.Z);

            Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);

            if (IsSliding())
            {
                Velocity = FVector(Velocity.X * ForwardJumpMultiplier, Velocity.Y * ForwardJumpMultiplier, Velocity.Z);
            }

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
        // DrawDebugLine(GetWorld(), Hit.Location, Hit.Location + HitForward * 1000.0f, FColor::Emerald, false, 50.0f, 4.0f);

        FVector Normal2D = Hit.Normal.GetSafeNormal2D();
        FVector DownwardAccel = Normal2D + FVector::DownVector;
        Velocity = SlidingAccelerationMultiplier * DownwardAccel;

        const FVector Adjusted =  Velocity * deltaTime;

        SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);

    }
}

bool UFPCharacterMovementComponent::CanAttemptJump() const 
{
	return IsJumpAllowed() &&
		   !bWantsToCrouch &&
		   (IsMovingOnGround() || IsFalling() || IsSliding()); // Falling included for double-jump and non-zero jump hold time, but validated by character.
}

bool UFPCharacterMovementComponent::IsSliding() const 
{
    return (MovementMode == MOVE_Custom) && UpdatedComponent;
}
