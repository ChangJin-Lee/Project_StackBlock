// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	if(InGameWidgetClass != nullptr)
	{
		InGameWidget = CreateWidget<UUserWidget>(GetWorld(), InGameWidgetClass);

		if(InGameWidget != nullptr)
		{
			InGameWidget->AddToViewport();
		}
	}
	
}
