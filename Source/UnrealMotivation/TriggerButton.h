// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivatableInterface.h"
#include "TriggerButton.generated.h"

UCLASS()
class UNREALMOTIVATION_API ATriggerButton : public AActor, public IActivatableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerButton();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ButtonMesh;

	FVector PressedLocation;

	void Activate(AActor* Sender);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
