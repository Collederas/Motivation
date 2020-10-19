// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryItem.h"
#include "InventoryComponent.h"
#include "Pickup.generated.h"

UCLASS()
class UNREALMOTIVATION_API APickup : public AStaticMeshActor
{
	GENERATED_BODY()

private:
	// Inventory representation of this Pickup
	UInventoryItem* InventoryItem;
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	UInventoryItem* SerializeInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void AddToInventory(UInventoryComponent* Inventory);

	UPROPERTY(EditAnywhere)
	bool Equippable = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	bool Equipped = false;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void SetEquipped(bool Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Serialize the current actor into an instance of UInventoryItem. **/
	UInventoryItem* MakeInventoryItem();
};
