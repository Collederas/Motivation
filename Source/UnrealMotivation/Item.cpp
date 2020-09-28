// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
    Name = FText::FromString("Item name");
}

UItem* UItem::Make(FString Name, TSubclassOf<AActor> ClassType)
{
    UItem* item = NewObject<UItem>();
    item->Name = FText::FromString(Name);
    item->ClassType = ClassType;
    return item;
}
