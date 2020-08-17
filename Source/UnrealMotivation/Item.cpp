// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
    name = FText::FromString("Item name");
}

UItem* UItem::Make(FString name)
{
    UItem* item = NewObject<UItem>();
    item->name = FText::FromString(name);
    return item;
}