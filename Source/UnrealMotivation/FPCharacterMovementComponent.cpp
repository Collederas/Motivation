// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacterMovementComponent.h"

void UFPCharacterMovementComponent::PhysFalling(float deltaTime, int32 Iterations)
{   
    float VelocityZ = this->GetLastUpdateVelocity().Z;

    // TArray< FStringFormatArg > args;
    // args.Add( FStringFormatArg( FString::SanitizeFloat(velocityZ) ) );

    // FString string = FString::Format( TEXT( "VelocityZ = {0}" ), args );
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, string);

    if (VelocityZ < 0)
    {
        // WIP - Next up: Add floor check to the if to determine that you are sliding
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Sliding");
    }
    Super::PhysFalling(deltaTime, Iterations);
}

void UFPCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{

}