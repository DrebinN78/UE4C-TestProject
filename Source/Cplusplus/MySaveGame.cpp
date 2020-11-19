// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

UMySaveGame::UMySaveGame()
{

};

void UMySaveGame::SetSaveData(FVector playerLocation, FRotator playerRotation, float playerHealth)
{
	playerLocationData = playerLocation;
	playerRotationData = playerRotation;
	playerHealthData = playerHealth;
}
