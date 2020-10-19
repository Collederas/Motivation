// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "FPCharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "InventoryItem.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPCharacter

AFPCharacter::AFPCharacter(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFPCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Bind Inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InventoryComponent->OnItemUsed.AddUObject(this, &AFPCharacter::OnItemUsed);
	InventoryComponent->EquipItemDelegate.BindUObject(this, &AFPCharacter::Equip);

	// Equippable object bindings
	EquippableObject = CreateDefaultSubobject<USceneComponent>(TEXT("EquipLocation"));
	EquippableObject->SetupAttachment(FirstPersonCameraComponent);

	EquippableObjectShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShootLocation"));
	EquippableObjectShootPoint->SetupAttachment(EquippableObject);

	// Set custom movement component to allow for custom movement modes
	UFPCharacterMovementComponent *MovementComponent = Cast<UFPCharacterMovementComponent>(GetCharacterMovement());

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void AFPCharacter::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// TEST ITEM DELEGATE BINDING

void AFPCharacter::OnItemUsed(UInventoryItem *item)
{
	FString itemName = item->Name;
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(itemName));

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, itemName);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPCharacter::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPCharacter::LookUpAtRate);
}

void AFPCharacter::Fire(TSubclassOf<AActor> ProjectileClass)
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld *const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();

			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((EquippableObjectShootPoint != nullptr) ? EquippableObjectShootPoint->GetComponentLocation() : GetActorLocation());

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		}
	}
}

void AFPCharacter::Equip(UInventoryItem *Item)
{

	if (Item->Equippable)
	{	
		APickup* EquipActor = (APickup*)UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Item->ClassType, EquippableObject->GetComponentTransform(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn, this);
		EquipActor->Equipped = true;
		EquipActor->FinishSpawning(EquippableObject->GetComponentTransform());
		FAttachmentTransformRules TransformRules = FAttachmentTransformRules( EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		EquipActor->AttachToComponent(EquippableObject, TransformRules);
		EquippedObject = EquipActor;
	}
}

APickup* AFPCharacter::GetCurrentEquippedObject() 
{
	return EquippedObject;
}

void AFPCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
