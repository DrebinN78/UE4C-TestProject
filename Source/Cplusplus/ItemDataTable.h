// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSPLUS_API UItemDataTable : public UDataTable
{
	GENERATED_BODY()
};



USTRUCT(BlueprintType)
struct FItemRowBase : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:

    FItemRowBase()
    {
        ItemName = "empty";
        ItemDescription = "empty";
        ItemValue = 0;
        ItemSprite = nullptr;
    }

    FItemRowBase(FString NewItemName, FString NewItemDesc, int NewItemValue, TSoftObjectPtr<UTexture> NewItemSprite)
    {
        ItemName = NewItemName;
        ItemDescription = NewItemDesc;
        ItemValue = NewItemValue;
        ItemSprite = NewItemSprite;
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FString ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int32 ItemValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TSoftObjectPtr<UTexture> ItemSprite;
};

UCLASS()
class CPLUSPLUS_API UGameItem : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int32 id;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString Name;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString Description;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        int32 Value;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        TSoftObjectPtr<UTexture> Sprite;
    UFUNCTION(BlueprintCallable)
        static UGameItem* CreateItem(FItemRowBase itemDBEntry);
};
