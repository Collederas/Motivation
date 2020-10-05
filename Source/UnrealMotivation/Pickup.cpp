// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

UInventoryItem* APickup::GetInventoryItem()
{
	return InventoryItem;
}

void APickup::SetInventoryItem()
{
	InventoryItem = MakeInventoryItem();
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	SetInventoryItem();
}

UInventoryItem* APickup::MakeInventoryItem()
{
	return UInventoryItem::Instantiate(GetName(), GetClass());
}

void APickup::AddTo(UInventoryComponent* Inventory)
{
	UInventoryItem* Item = GetInventoryItem();
	if (!Item) {
		return;
	}
	return Inventory->AddItem(Item);
}
