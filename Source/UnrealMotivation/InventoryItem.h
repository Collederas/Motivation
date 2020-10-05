// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GunProjectileBase.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UNREALMOTIVATION_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
 	static UInventoryItem* Instantiate(FString Name, TSubclassOf<AActor> ClassType);

	/** Spawn an Actor from the UInventoryItem properties. */
	// UFUNCTION(BlueprintCallable, Category = "Item")
	// Spawn(FVector Location, FRotator Rotation);

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(SimpleDisplay)
	FGuid Uuid;

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ClassType;
};
