// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Widget.h"

#include "TimerManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

UBase_Widget::UBase_Widget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 사운드 에셋을 찾아서 ClickSound에 할당합니다.
	static ConstructorHelpers::FObjectFinder<USoundBase> ClickSoundAsset(TEXT("/Script/Engine.SoundWave'/Engine/VREditor/Sounds/UI/Click_on_Button.Click_on_Button'"));
	if (ClickSoundAsset.Succeeded())
	{
		ClickSound = ClickSoundAsset.Object;
	}
}


void UBase_Widget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBase_Widget::ButtonClick()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ClickSound);
}
