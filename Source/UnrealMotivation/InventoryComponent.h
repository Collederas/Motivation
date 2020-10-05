// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Pickup.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_EVENT_OneParam(UInventoryComponent, FOnItemUsed, UInventoryItem *);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALMOTIVATION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadWrite, Category = "Inventory")
	TArray<class UInventoryItem *> Items;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void UseItem(UInventoryItem *Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void AddItem(UInventoryItem *Item);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InfiniteObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APickup> InfiniteObjectsClass;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool Contains(UInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void RemoveItem(UInventoryItem* Item);

	FOnItemUsed OnItemUsed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual TArray<class UInventoryItem *> GetContent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool IsEmpty();
};
