// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GunProjectileBase.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UNREALMOTIVATION_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
 	static UItem* Make(FString Name, TSubclassOf<AActor> ClassType);

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ClassType;
};
