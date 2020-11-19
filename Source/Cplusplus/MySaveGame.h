// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSPLUS_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public :

	UMySaveGame();

	UPROPERTY()
	FVector playerLocationData;

	UPROPERTY()
	FRotator playerRotationData;

	UPROPERTY()
	float playerHealthData;

	UPROPERTY()
	TArray<FName> loadedStreamLevelsData;

	UFUNCTION()
	void SetSaveData(FVector playerLocation, FRotator playerRotation, float playerHealth);
};
