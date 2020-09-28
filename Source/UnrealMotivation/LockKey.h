// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "LockKey.generated.h"

UCLASS()
class UNREALMOTIVATION_API ALockKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// The related inventory item
	UPROPERTY(BlueprintReadWrite)
	UItem* InventoryItem;
};
