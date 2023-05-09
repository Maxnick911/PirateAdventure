// Pirate Adventure Game Vietokhin AD211

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PAPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PIRATEADVENTURE_API UPAPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
    float GetStaminaPercent() const;
};
