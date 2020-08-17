// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UNREALMOTIVATION_API UItem : public UObject
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Item")
 	static UItem* Make(FString name);

public:
	UItem();

	UPROPERTY(SimpleDisplay, EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText name;
};
