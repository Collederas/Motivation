// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActivatableInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UActivatableInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREALMOTIVATION_API IActivatableInterface
{
	GENERATED_BODY()

public:
/** A version of ActivatableInterface that can be implemented in Blueprint. */
UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Activatable Interface")
void Activate(AActor* Sender);
};
