// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Weapon/PAMusket.h>
#include "PAPlayerHUDWidget.generated.h"

UCLASS()
class PIRATEADVENTURE_API UPAPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


    UFUNCTION(BlueprintCallable, Category = "HUD")
    float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
    float GetStaminaPercent() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
    bool GetMusketAmmoData(FAmmoData& AmmoData) const;
};
