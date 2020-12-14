// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "CplusplusCharacter.h"

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	PlayerAudioComponent = Cast<ACplusplusCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetAudioComponent();
	PlayerAudioComponent->SetSound(AmbientSoundList[0]);
	PlayerAudioComponent->Play();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::ChangeMusic(int MusicNumber)
{
	PlayerAudioComponent->Stop();
	PlayerAudioComponent->SetSound(AmbientSoundList[MusicNumber]);
	PlayerAudioComponent->Play();
}



