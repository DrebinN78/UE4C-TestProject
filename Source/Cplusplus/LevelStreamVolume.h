// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CplusplusCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "LevelStreamVolume.generated.h"

UCLASS()
class CPLUSPLUS_API ALevelStreamVolume : public AActor
{
	GENERATED_BODY()

private:
	// Overlap volume to trigger level streaming
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapVolume;

public:	
	// Sets default values for this actor's properties
	ALevelStreamVolume();

	UPROPERTY(EditAnywhere)
	TArray<FName> LevelsToLoad;

	UPROPERTY(EditAnywhere)
	TArray<FName> LevelsToUnload;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateStreamedLevels();

	UFUNCTION()
	void OverlapBegins(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
