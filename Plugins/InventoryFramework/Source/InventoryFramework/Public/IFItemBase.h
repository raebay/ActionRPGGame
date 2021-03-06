// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "IFItemBase.generated.h"

/*
	A Struct where the actuall item is contained (so it can be easy serialized/deserialized from json. 
	Also allows to easily embed a replicate itemsh within items.
*/
USTRUCT(BlueprintType)
struct FIFItemBaseData
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class INVENTORYFRAMEWORK_API UIFItemBase : public UObject
{
	GENERATED_BODY()
public:
	
	//Possibly just one index, if we are going to bypass unreal replication
	//and just send items as json from server and then decode them and insert in map.
	UPROPERTY()
		uint8 LocalIndex;
	UPROPERTY()
		uint8 NetIndex;

	bool IsNameStableForNetworking() const override
	{
		return false;
	}

	bool IsSupportedForNetworking() const override
	{
		return true;
	}
	
	bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;

	/*
		Called after item has been added to inventory.
	*/
	virtual void OnItemAdded(uint8 LocalIndex) {};
	/*
		Called when item changed slots within THE SAME inventory;
	*/
	virtual void OnItemChanged(uint8 LocalIndex) {};
	/*
		Called after item has been removed from inventory;
	*/
	virtual void OnItemRemoved(uint8 LocalIndex) {};

	virtual void PreItemLoad() {};

	virtual void PostItemLoad() {};

	static UIFItemBase* LoadFromJSON() { return nullptr; }

	template<typename ItemType, typename DataType>
	static ItemType* CreateItemFromData(DataType InData, class UIFInventoryComponent* Owner)
	{
		ItemType* Item = NewObject<ItemType>(Owner, ItemType::StaticClass());
		Item->Data = InData;
		return Item;
	}

	template<typename ItemType, typename DataType>
	static ItemType* CreateItemFromData(DataType InData, TSubclassOf<ItemType> ItemClass, class UIFInventoryComponent* Owner)
	{
		ItemType* Item = NewObject<ItemType>(Owner, ItemClass);
		Item->Data = InData;
		return Item;
	}
};
