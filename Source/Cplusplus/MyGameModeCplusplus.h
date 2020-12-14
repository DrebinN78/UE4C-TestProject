// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataTable.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeCplusplus.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSPLUS_API AMyGameModeCplusplus : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AMyGameModeCplusplus();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* ItemDataTable;
	void QuitGame();
	FORCEINLINE UDataTable* GetItemDataSheet() const { return ItemDataTable; }
private:
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
