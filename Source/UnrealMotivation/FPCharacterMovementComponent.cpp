// Fill out your copyright notice in the Description page of Project Settings.

#include "FPCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

UFPCharacterMovementComponent::UFPCharacterMovementComponent()
{
    
}

bool UFPCharacterMovementComponent::DoJump(bool bReplayingMoves)
{   
    if (CharacterOwner && CharacterOwner->CanJump())
    {
        // Don't jump if we can't move up/down.
        if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
        {

            Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
            UE_LOG(LogTemp, Log, TEXT("Velocity: %s"), *Velocity.ToString());

            if (IsSliding())
            {
                // Clamp the angle between floor and normal

                FHitResult Hit(1.f);
                FCollisionQueryParams CollisionParams;

                bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 200), ECC_Visibility, CollisionParams);

                FVector VelocityGroundProject = FVector::VectorPlaneProject(Velocity, Hit.Normal.GetSafeNormal());

                float VelDotProduct = FVector::DotProduct(Velocity.GetSafeNormal(), VelocityGroundProject.GetSafeNormal());

                if (FMath::Acos(VelDotProduct) > MaxJumpRotation){
                    FVector RotatedVel = Velocity.RotateAngleAxis(FMath::RadiansToDegrees(MaxJumpRotation), CharacterOwner->GetRootComponent()->GetRightVector());
                    Velocity = RotatedVel.GetSafeNormal() * SlidingJumpBoost;
                }
                UE_LOG(LogTemp, Log, TEXT("Velocity after: %s"), *Velocity.ToString());

                // DrawDebugLine(GetWorld(), Hit.Location, Hit.Location + Velocity, FColor::Red, false, 50.0f, 4.0f);

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

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 2500), ECC_Visibility, CollisionParams);


    if (bHit && !IsWalkable(Hit)) {
        // ### DEBUG UTILITIES ###
        // DrawDebugLine(GetWorld(), Hit.Location, Hit.Location + HitForward * 1000.0f, FColor::Emerald, false, 50.0f, 4.0f);
        // UE_LOG(LogTemp, Log, TEXT("Acceleration: %s"), *Acceleration.ToString());
        // ###

        FVector Normal2D = Hit.Normal.GetSafeNormal2D();
        // Basic "Piano inclinato" memories from high school
        // Adding gravity (DownVector) to the normal, results in a vector that is parallel to the plane.
        FVector DownwardVel = Normal2D + FVector::DownVector;

        // Then we project the character's current velocity onto the plane.
        Velocity = Velocity.ProjectOnTo(DownwardVel);
        
        // If velocity is upwards, invert it.
        if (FVector::DotProduct(Velocity.GetSafeNormal(), DownwardVel.GetSafeNormal()) < 0)
            Velocity *= -1;

        // Force Velocity to the Max when sliding
        Velocity = Velocity.GetSafeNormal() * SlidingSpeed;

        // Now let's add acceleration to control the movement only laterally.
        FVector SlideAcceleration = FVector::VectorPlaneProject(Acceleration, Normal2D);

        // Prevent that pressing full back or forward moves the character right/left (right, Polar in Crash Bandicoot 4?)
        float AccelDotP = FMath::Abs(FVector::DotProduct(Acceleration.GetSafeNormal2D(), CharacterOwner->GetRootComponent()->GetRightVector()));
        Acceleration = SlideAcceleration * AccelDotP * SlidingAccelerationControl;
        
        // Apply sliding velocity and acceleration to current velocity
        // Velocity += SlidingVelocityMultiplier * DownwardVel;

        Velocity += Acceleration * deltaTime;
        

        // Move
        FVector Adjusted = Velocity.GetClampedToMaxSize(MaxCustomMovementSpeed) * deltaTime;

        SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);
        SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
        
    } else {
        SetMovementMode(MOVE_Falling);
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
