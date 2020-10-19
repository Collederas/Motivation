// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UNREALMOTIVATION_API UInventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	static UInventoryItem *Instantiate(FString Name, TSubclassOf<AActor> ClassType, UStaticMesh* Mesh = nullptr, bool Equippable = false);

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FString Name = "Item";

	UPROPERTY(SimpleDisplay)
	FGuid Uuid;

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ClassType;

	UPROPERTY(SimpleDisplay, EditDefaultsOnly)
	UStaticMesh *Mesh;

	// Determines if Character can equip this object.
	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool Equippable = false;
};
