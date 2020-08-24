// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// UDELEGATE(BlueprintCallable, Category = "Inventory")
DECLARE_EVENT_OneParam(UInventoryComponent, FOnItemUsed, UItem *);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALMOTIVATION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadWrite, Category = "Inventory")
	TArray<class UItem *> Items;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void UseItem(UItem *item);

	FOnItemUsed OnItemUsed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void Add(UItem *item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void RemoveItem(UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual TArray<class UItem *> GetContent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool IsEmpty();
};
