// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelStreamVolume.h"

// Sets default values
ALevelStreamVolume::ALevelStreamVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	RootComponent = OverlapVolume;
}

// Called when the game starts or when spawned
void ALevelStreamVolume::BeginPlay()
{
	Super::BeginPlay();
	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &ALevelStreamVolume::OverlapBegins);
}

void ALevelStreamVolume::UpdateStreamedLevels()
{
	for (FName level : LevelsToUnload)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::UnloadStreamLevel(this, level, LatentInfo, false);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Unloaded : ") + level.GetPlainNameString());
	}
	
	for (FName level : LevelsToLoad)
	{
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(this, level, true, false, LatentInfo);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Loaded : ") + level.GetPlainNameString());
	}
}

// Called every frame
void ALevelStreamVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelStreamVolume::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == MyCharacter)
	{
		UpdateStreamedLevels();
	}
}

