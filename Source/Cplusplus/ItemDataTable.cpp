// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ItemDataTable.h"

UGameItem* UGameItem::CreateItem(FItemRowBase itemDBEntry)
{
	UGameItem* item = NewObject<UGameItem>();
	item->Name = itemDBEntry.ItemName;
	item->Description = itemDBEntry.ItemDescription;
	item->Value = itemDBEntry.ItemValue;
	item->Sprite = itemDBEntry.ItemSprite;
	return item;
}
