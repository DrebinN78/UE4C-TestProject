// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PainVolume.generated.h"

UCLASS()
class CPLUSPLUS_API APainVolume : public AActor
{
	GENERATED_BODY()

private:
	// Overlap volume to trigger level streaming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	APainVolume();
	// Damage ammount to our player
	UPROPERTY(EditAnywhere)
	float damagePerFrame;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
