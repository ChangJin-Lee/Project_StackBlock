// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidget.h"

#include "DefaultGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(PressToStartButton)
	{
		PressToStartButton->OnClicked.AddDynamic(this, &UInGameWidget::OnClickToStart);
	}
}

void UInGameWidget::UpdateUI(const bool bIsStacked, const int32 Attempts, const int32 Height) const
{
	if(bIsStacked)
	{
		if(StackedHeight)
		{
			FString ValueString = FString::FromInt(Height);
			StackedHeight->SetText(FText::FromString(ValueString));
		}
	}
	else
	{
		if(Remaining)
		{
			FString ValueString = FString::FromInt(Attempts);
			Remaining->SetText(FText::FromString(ValueString));
		}
	}
}

void UInGameWidget::OnClickToStart()
{
	if(UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.SetTimer(TimerHandle, this, &UInGameWidget::DelaySpawnBlock, 1.0f, false);
	}
}

void UInGameWidget::DelaySpawnBlock()
{
	if(UDefaultGameInstance* DefaultGameInstance = Cast<UDefaultGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		DefaultGameInstance->OnSpawnBlock();
	}
}
