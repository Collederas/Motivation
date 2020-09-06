// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerButton.h"

// Sets default values
ATriggerButton::ATriggerButton()
{
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonMesh"));
	ButtonMesh->SetupAttachment(VisualMesh);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATriggerButton::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

// Called every frame
void ATriggerButton::Activate_Implementation(AActor* Sender)
{
	SetActorTickEnabled(true);
}

void ATriggerButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ButtonLocation = ButtonMesh->GetRelativeLocation();
	ButtonMesh->SetRelativeLocation(FMath::Lerp(ButtonLocation, PressedLocation, 0.03f), false);
}
