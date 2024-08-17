// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"

#include "DefaultGameInstance.h"
#include "GameOverWidget.h"
#include "InGameWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	if(InGameWidgetClass == nullptr)
	{
		static ConstructorHelpers::FClassFinder<UInGameWidget> WidgetClassFinder(TEXT("/Game/UI/WBP_InGame"));
		InGameWidgetClass = WidgetClassFinder.Class;
	}

	if(GameOverWidgetClass == nullptr)
	{
		static ConstructorHelpers::FClassFinder<UGameOverWidget> WidgetClassFinder(TEXT("/Game/UI/WBP_GameOver"));
		GameOverWidgetClass = WidgetClassFinder.Class;
	}
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnBlockStacked.AddDynamic(this, &ADefaultPlayerController::OnBlockStacked);
		StageClearHeight = DefaultGameInstance->GetStageClearHeight();
		AttempCount = DefaultGameInstance->GetAttemptCount();
	}
	
	if(InGameWidgetClass != nullptr)
	{
		InGameWidget = CreateWidget<UInGameWidget>(GetWorld(), InGameWidgetClass);

		if(InGameWidget != nullptr)
		{
			InGameWidget->AddToViewport();
		}
	}	
	
	UpdateInGameWidget(false, AttempCount, StackedHeight);
}

void ADefaultPlayerController::OnBlockStacked(bool IsStacked)
{
	if(IsStacked)
	{
		StackedHeight++;
	}
	else
	{
		if(AttempCount > 0)
		{
			AttempCount--;
		}
	}

	UpdateInGameWidget(IsStacked, AttempCount, StackedHeight);
	
	if(StackedHeight >= StageClearHeight)
	{
		bIsStageFailed = false;
		OnGameOver();
	}
	else if(AttempCount <= 0)
	{
		bIsStageFailed = true;
		OnGameOver();
	}
	else
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefaultPlayerController::SpawnNewBlock, 1.0f, false);
	}
}

void ADefaultPlayerController::SpawnNewBlock()
{
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->CallOnSpawnBlock.Broadcast();
	}
}

void ADefaultPlayerController::OnGameOver()
{	
	if(GameOverWidgetClass != nullptr)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);

		if(GameOverWidget != nullptr)
		{
			GameOverWidget->AddToViewport();
			GameOverWidget->SetGameOverPanel(bIsStageFailed);

			if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
			{
				DefaultGameInstance->CallOnGameOver.Broadcast();
			}
		}
	}
}

void ADefaultPlayerController::UpdateInGameWidget(const bool bIsStacked, const int32 Attempts, const int32 Height) const
{
	InGameWidget->UpdateUI(bIsStacked, Attempts, Height);
}
