// Fill out your copyright notice in the Description page of Project Settings.


#include "LockKey.h"

// Sets default values
ALockKey::ALockKey()
{

}

// Called when the game starts or when spawned
void ALockKey::BeginPlay()
{
	Super::BeginPlay();
	InventoryItem = UItem::Make(GetName(), GetClass());
}

