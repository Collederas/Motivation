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

// void UFPCharacterMovementComponent::PhysCustomSliding(float deltaTime, int32 Iterations)
// {
//     float remainingTime = deltaTime;

//     while (Iterations < MaxSimulationIterations)
//     {
//         Iterations++;
//         float timeTick = GetSimulationTimeStep(remainingTime, Iterations);
//         remainingTime -= timeTick;

//         FHitResult Hit(1.f);
//         FStepDownResult *OutStepDownResult;
//         const float MaxDecel = GetMaxBrakingDeceleration();

//         CalcVelocity(timeTick, 1, false, MaxDecel);

//         const FVector Gravity(0.f, 0.f, GetGravityZ());
//         float GravityTime = timeTick;
//         Velocity = NewFallVelocity(Velocity, Gravity, GravityTime);

//         FVector Adjusted = 0.5f * Velocity * timeTick;

//         SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);
//         // GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Sliding and input is %d"), AnalogInputModifier));
//     }
// float remainingTime = deltaTime;

// while ((remainingTime >= MIN_TICK_TIME) && Iterations < MaxSimulationIterations)
// {
//     Iterations++;
//     const float timeTick = GetSimulationTimeStep(remainingTime, Iterations);
//     remainingTime -= timeTick;

//     Velocity = FVector(-1000.0f, 0, 0);
//     FString DebugMsg = FString::Printf(TEXT("Velocity is set to %s"), *(Velocity.ToString()));
//     GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Yellow, DebugMsg);
//     //  UE_LOG(LogTemp, Warning, TEXT("Current: %s"), *(myResult.Location.ToString()));
// }

// SlideAlongSurface(Delta, 1.f - PercentTimeApplied, Hit.Normal, Hit, true);
// }

FVector UFPCharacterMovementComponent::HandleSlopeBoosting(const FVector &SlideResult, const FVector &Delta, const float Time, const FVector &Normal, const FHitResult &Hit) const
{
    return SlideResult;
}
