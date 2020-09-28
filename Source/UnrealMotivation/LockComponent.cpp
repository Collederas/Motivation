#include "LockComponent.h"

// Sets default values for this component's properties
ULockComponent::ULockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Locked = true;
}


// Called when the game starts
void ULockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULockComponent::Lock()
{
	return;
}

bool ULockComponent::Unlock(UInventoryComponent* Inventory)
{
	if (Inventory->Contains(Key->InventoryItem))
	{
		UE_LOG(LogTemp, Warning, TEXT("Unlocked"));
		Inventory->RemoveItem(Key->InventoryItem);
		Locked = false;
	}
	return Locked;
}
