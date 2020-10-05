/* Use APickup to manage locking and unlocking mechanics against
   UInventoryItem */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.h"
#include "LockComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALMOTIVATION_API ULockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="LockComponent")
	UInventoryItem* Key;

	UPROPERTY(BlueprintReadWrite, Category="LockComponent")
	bool Locked;

	UFUNCTION(BlueprintCallable)
	bool Unlock(UInventoryComponent* Inventory);
};
