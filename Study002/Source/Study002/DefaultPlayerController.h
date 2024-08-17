// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UInGameWidget;
class UGameOverWidget;
/**
 * 
 */
UCLASS()
class STUDY002_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADefaultPlayerController();
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBlockStacked(bool IsStacked);
	
	void OnGameOver();

	int32 GetStackedHeight() const { return StackedHeight; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInGameWidget> InGameWidgetClass = nullptr;

	UPROPERTY()
	UInGameWidget* InGameWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameOverWidget> GameOverWidgetClass = nullptr;
	
	UPROPERTY()
	UGameOverWidget* GameOverWidget = nullptr;
	
	int32 StackedHeight = 0;
	int32 StageClearHeight = 0;
	int32 AttempCount = 0;

	bool bIsStageFailed = false;

	void UpdateInGameWidget(bool bIsStacked, int32 Attempts, int32 Height) const;

	void SpawnNewBlock();
	FTimerHandle TimerHandle; 
};
