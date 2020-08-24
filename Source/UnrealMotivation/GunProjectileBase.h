// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GunProjectileBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMOTIVATION_API AGunProjectileBase : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "GunProjectile", meta=(ExposeOnSpawn="true"))
	bool IsProjectile;

	UPROPERTY(BlueprintReadWrite, Category = "GunProjectile", meta=(ExposeOnSpawn="true"))
	float ProjectileInitialSpeed;
};
