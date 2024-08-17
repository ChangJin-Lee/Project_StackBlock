// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Widget.h"
#include "InGameWidget.generated.h"


class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class STUDY002_API UInGameWidget : public UBase_Widget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PressToStartButton;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Remaining;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackedHeight;
	
	
	void UpdateUI(bool bIsStacked, int32 Attempts, int32 Height) const;
	
private:
	UFUNCTION()
	void OnClickToStart();

	void DelaySpawnBlock();
	FTimerHandle TimerHandle; 
};
