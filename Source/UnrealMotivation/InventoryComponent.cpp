// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	InfiniteObjects = true;

	if (InfiniteObjects)
	{

		for (int i = 0; i <= 100; i++)
		{
			UItem *ItemToAdd = UItem::Make("Debug_Object", InfiniteObjectsClass);
			UE_LOG(LogTemp, Warning, TEXT("AddingItems"));
			Items.Add(ItemToAdd);
		}
	}
}

void UInventoryComponent::Add(UItem *item)
{
	FString itemName = item->Name.ToString();
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(itemName));

	FString string = FString::Format(TEXT("Adding {0} to inventory"), args);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, string);
	Items.Add(item);
}

void UInventoryComponent::RemoveItem(UItem *Item)
{
	Items.Remove(Item);
}

TArray<class UItem *> UInventoryComponent::GetContent()
{
	return Items;
}

bool UInventoryComponent::IsEmpty()
{
	return Items.Num() > 0 ? false : true;
}

void UInventoryComponent::UseItem(UItem *item)
{
	OnItemUsed.Broadcast(item);
}
