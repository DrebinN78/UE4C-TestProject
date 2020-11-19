// Fill out your copyright notice in the Description page of Project Settings.


#include "PainVolume.h"
#include "CplusplusCharacter.h"

// Sets default values
APainVolume::APainVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;
}

// Called when the game starts or when spawned
void APainVolume::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APainVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TSet<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, TSubclassOf<ACharacter>());
	for (AActor* Elem : overlappingActors)
	{
		((ACplusplusCharacter*)Elem)->health -= damagePerFrame;
	}
}



