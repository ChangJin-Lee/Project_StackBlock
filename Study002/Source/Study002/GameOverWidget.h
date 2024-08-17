// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_Widget.h"
#include "GameOverWidget.generated.h"

class UCanvasPanel;

/**
 * 
 */
UCLASS()
class STUDY002_API UGameOverWidget : public UBase_Widget
{
	GENERATED_BODY()


public:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GameOverPanel;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CompleteStagePanel;

	void SetGameOverPanel(bool IsFailedStage) const;
};
