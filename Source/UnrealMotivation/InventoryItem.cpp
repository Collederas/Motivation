// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
    Name = "Item";
}

UInventoryItem *UInventoryItem::Instantiate(FString Name, TSubclassOf<AActor> ClassType, UStaticMesh *Mesh, bool Equippable)
{
    UInventoryItem *item = NewObject<UInventoryItem>();
    item->Name = Name;
    item->ClassType = ClassType;
    item->Uuid = FGuid::NewGuid();
    item->Equippable = Equippable;
    item->Mesh = Mesh;
    return item;
}