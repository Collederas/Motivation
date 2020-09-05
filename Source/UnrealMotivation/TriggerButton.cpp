// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerButton.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATriggerButton::ATriggerButton()
{
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(VisualMesh);

	PressedLocation = ButtonMesh-> GetComponentLocation() - FVector(50, 0, 0);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATriggerButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATriggerButton::Activate(AActor* Sender)
{
	SetActorTickEnabled(true);
}

void ATriggerButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ButtonMesh->SetRelativeLocation(FMath::Lerp(ButtonMesh->GetComponentLocation(), PressedLocation), 0.01f);
	if (ButtonMesh->GetComponentLocation() == PressedLocation)
	{
		SetActorTickEnabled(false);
	}
}
