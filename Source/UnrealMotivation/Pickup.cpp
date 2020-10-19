// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

UInventoryItem* APickup::SerializeInventoryItem()
{
	return InventoryItem;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	InventoryItem = MakeInventoryItem();
}

UInventoryItem* APickup::MakeInventoryItem()
{
	return UInventoryItem::Instantiate(GetName(), GetClass(), GetStaticMeshComponent()->GetStaticMesh(), Equippable);
}

void APickup::AddToInventory(UInventoryComponent* Inventory)
{
	UInventoryItem* Item = SerializeInventoryItem();
	if (!Item) {
		return;
	}
	return Inventory->AddItem(Item);
}

void APickup::SetEquipped(bool Value) 
{
	Equipped = Value;
}
