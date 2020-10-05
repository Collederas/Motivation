// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryItem.h"

UInventoryItem::UInventoryItem()
{
    Name = FText::FromString("Item name");
}

UInventoryItem *UInventoryItem::Instantiate(FString Name, TSubclassOf<AActor> ClassType)
{
    UInventoryItem *item = NewObject<UInventoryItem>();
    item->Name = FText::FromString(Name);
    item->ClassType = ClassType;
    item->Uuid = FGuid::NewGuid();
    return item;
}