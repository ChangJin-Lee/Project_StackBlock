// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "Components/CanvasPanel.h"

void UGameOverWidget::SetGameOverPanel(bool IsFailedStage) const
{
	if(GameOverPanel && CompleteStagePanel)
	{
		// stage failed 
		if(IsFailedStage)
		{
			GameOverPanel->SetVisibility(ESlateVisibility::Visible);
			CompleteStagePanel->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			GameOverPanel->SetVisibility(ESlateVisibility::Hidden);
			CompleteStagePanel->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
