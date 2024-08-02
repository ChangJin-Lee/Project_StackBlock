// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Base_Widget.generated.h"

/**
 * 
 */
UCLASS()
class STUDY002_API UBase_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBase_Widget(const FObjectInitializer& ObjectInitializer);

	// 위젯 초기화 함수
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ClickSound;

protected:
	// 버튼 클릭 이벤트 처리 함수
	UFUNCTION(BlueprintCallable)
	void ButtonClick();
	
};


