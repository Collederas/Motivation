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


bool ULockComponent::Unlock(UInventoryComponent* Inventory)
{
	if (Inventory->Contains(Key))
	{
		Locked = false;
		return true;
	}
	return false;
}
