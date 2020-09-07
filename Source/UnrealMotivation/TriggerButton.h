// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActivatableInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerButton.generated.h"

UCLASS(Blueprintable)
class UNREALMOTIVATION_API ATriggerButton : public AActor, public IActivatableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATriggerButton();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *ButtonMesh;

	/** Material to use when the button is active **/
	UPROPERTY(EditAnywhere)
	UMaterial *ActiveMaterial;

	UPROPERTY(EditAnywhere)
	TArray<AActor *> ControlledObjects;

	void Activate_Implementation(AActor *Sender) override;
	void Deactivate_Implementation(AActor *Sender) override;
	void Toggle_Implementation(AActor *Sender) override;
	void SetMaterial();

protected:
	/** Default original material **/
	UMaterialInterface *OriginalMaterial;

	/** Keep track of the Interface state **/
	UPROPERTY(BlueprintReadWrite)
	bool IsActive = false;

	virtual void BeginPlay() override;
};
