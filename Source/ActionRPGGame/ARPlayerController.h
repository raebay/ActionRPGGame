// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
#include "IFInventoryComponent.h"
#include "IFInventoryInterface.h"
#include "ARPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGGAME_API AARPlayerController : public APlayerController, public IIFInventoryInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI")
		class UARUIComponent* UIComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI")
		class UARWeaponManagerComponent* WeaponManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI")
		class UARAbilityManagerComponent* AbilityManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI")
		class UIFInventoryComponent* MainInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		FGameplayTag InputNextWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		TSoftClassPtr<UGAAbilityBase> AbilitytNextWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		FGameplayTag InputPreviousWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		TSoftClassPtr<UGAAbilityBase> AbilitytPreviousWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		FGameplayTag InputHolsterWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		TSoftClassPtr<UGAAbilityBase> AbilitytHolstersWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		FGameplayTag InputSetAbilityGroup01;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		TSoftClassPtr<UGAAbilityBase> SetAbilityGroup01;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		FGameplayTag InputSetAbilityGroup02;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Input")
		TSoftClassPtr<UGAAbilityBase> SetAbilityGroup02;

	bool bInputBount;
public:
	AARPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Possess(APawn* aPawn) override;
	void SetupInputComponent();

	void InputSwitchAbilitySet();
	void InputShowHideAbilityManager();
	void InputShowHideInventory();
	void OnInputAbilityReady(TSoftClassPtr<UGAAbilityBase> InAbilityTag, FGameplayTag InInputTag);

	UFUNCTION(Client, Reliable)
		void ClientPossesed(APawn* InPawn);
	void ClientPossesed_Implementation(APawn* InPawn);

	UFUNCTION(BlueprintPure, Category = "Hud")
		float GetObjectScreenRadius(AActor* InActor);

	UFUNCTION(BlueprintPure, Category = "Hud")
		void GetObjectBoundSphere(float Distance, AActor* InActor, FVector& Origin, float& Radius, float& Scale
			, float& SphereRadius);

	/* IIFInventoryInterface */
	virtual void OnInventoryReplicated(class UIFInventoryComponent* Inventory) override;
	/* IIFInventoryInterface */

};
