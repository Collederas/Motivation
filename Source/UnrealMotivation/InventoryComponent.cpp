// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryItem.h"

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
			UInventoryItem *ItemToAdd = UInventoryItem::Instantiate("Debug_Object", InfiniteObjectsClass);
			Items.Add(ItemToAdd);
		}
	}
}

void UInventoryComponent::AddItem(UInventoryItem *Item)
{
	FString itemName = Item->Name;
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(itemName));

	FString string = FString::Format(TEXT("Adding {0} to inventory"), args);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, string);
	Items.Add(Item);
}

void UInventoryComponent::RemoveItem(UInventoryItem *Item)
{
	Items.Remove(Item);
}

bool UInventoryComponent::Contains(UInventoryItem *Item)
{
	return Items.ContainsByPredicate([Item] (const UInventoryItem* InternalItem) {
		return InternalItem->Uuid == Item->Uuid;
	});
}

TArray<class UInventoryItem *> UInventoryComponent::GetContent()
{
	return Items;
}

bool UInventoryComponent::IsEmpty()
{
	return Items.Num() > 0 ? false : true;
}

void UInventoryComponent::UseItem(UInventoryItem *item)
{
	OnItemUsed.Broadcast(item);
}
