// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::Add(UItem *item)
{
	FString itemName = item->name.ToString();
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(itemName));

	FString string = FString::Format(TEXT("Adding {0} to inventory"), args);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, string);
}

void UInventoryComponent::Remove()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Removing from inventory"));
}

void UInventoryComponent::GetContent()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Getting inventory conent"));
}

void UInventoryComponent::UseItem(UItem* item)
{
	OnItemUsed.Broadcast(item);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Broadcasting like crazyyy!!"));
}