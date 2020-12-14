// Fill out your copyright notice in the Description page of Project Settings.

#include "CplusplusCharacter.h"
#include "MyGameModeCplusplus.h"

AMyGameModeCplusplus::AMyGameModeCplusplus()
{
}

void AMyGameModeCplusplus::BeginPlay()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FInputModeGameOnly inputmode;
	playerController->SetInputMode(inputmode);
	playerController->bShowMouseCursor = false;
	if (OptionsString.Split("=", nullptr, nullptr))
	{
		ACplusplusCharacter* playerInstance = Cast<ACplusplusCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		playerInstance->LoadFromSave(Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("GameSaveFile", 0)));
	}
}

void AMyGameModeCplusplus::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}
