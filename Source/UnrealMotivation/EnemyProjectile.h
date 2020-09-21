// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"


UCLASS()
class UNREALMOTIVATION_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	class UStaticMeshComponent* MeshComponent;

	// Function that initializes the projectile's velocity in the shoot direction.
	UFUNCTION(BlueprintCallable)
	void FireInDirection(const FVector &ShootDirection);
};
