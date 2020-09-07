// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerButton.h"
#include "ActivatableInterface.h"

// Sets default values
ATriggerButton::ATriggerButton()
{
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(RootComponent);
	OriginalMaterial = ButtonMesh->GetMaterial(0);

	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATriggerButton::BeginPlay()
{
	Super::BeginPlay();
	if (!ActiveMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ActiveMaterial assigned"));
	}
}

void ATriggerButton::Activate_Implementation(AActor *Sender)
{
	// I'll leave this one here to remember how to Printf a TCHAR
	// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Emerald, FString::Printf(TEXT("Received input from: %s"), *Sender->GetName()));

	IsActive = true;
	ButtonMesh->SetMaterial(0, ActiveMaterial);

	if (ControlledObjects.Num() > 0)
	{
		for (int i = 0; i < ControlledObjects.Num(); i++)
		{
			AActor *ControlledObject = ControlledObjects[i];
			if (ControlledObject->GetClass()->ImplementsInterface(UActivatableInterface::StaticClass()))
			{
				IActivatableInterface::Execute_Activate(ControlledObject, this);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No valid UActivatableInterface found on %s"), *ControlledObject->GetName())
			}
		}
	}
}

void ATriggerButton::Deactivate_Implementation(AActor *Sender)
{
	IsActive = false;
	ButtonMesh->SetMaterial(0, OriginalMaterial);
	if (ControlledObjects.Num() > 0)
	{
		for (int i = 0; i < ControlledObjects.Num(); i++)
		{
			AActor *ControlledObject = ControlledObjects[i];
			if (ControlledObject->GetClass()->ImplementsInterface(UActivatableInterface::StaticClass()))
			{
				IActivatableInterface::Execute_Deactivate(ControlledObject, this);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No valid UActivatableInterface found on %s"), *ControlledObject->GetName())
			}
		}
	}
}
