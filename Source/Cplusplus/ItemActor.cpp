// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	ItemType = UGameItem::CreateItem(*Cast<AMyGameModeCplusplus>(UGameplayStatics::GetGameMode(GetWorld()))->GetItemDataSheet()->FindRow<FItemRowBase>(FName(FString::FromInt(ItemID)), FString::FromInt(0), true));
	OverlapVolume->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OverlapBegins);
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ACplusplusCharacter* MyCharacter = Cast<ACplusplusCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (OtherActor == MyCharacter)
	{
		MyCharacter->Inventory.Add(ItemType);
		this->Destroy();
	}
}


