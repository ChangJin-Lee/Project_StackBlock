// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameInstance.h"



// Event On Block Stacked 
void UDefaultGameInstance::OnBlockStacked(const bool IsStacked) const
{
	CallOnBlockStacked.Broadcast(IsStacked);
}

void UDefaultGameInstance::OnBlockUpdateLocation(const FVector& NewLocation) const
{
	CallOnBlockUpdateLocation.Broadcast(NewLocation);
}

void UDefaultGameInstance::OnDropBlock() const
{
	CallOnDropBlock.Broadcast();
}

void UDefaultGameInstance::OnSpawnBlock() const
{
	CallOnSpawnBlock.Broadcast();
}

void UDefaultGameInstance::OnGameOver() const
{
	CallOnGameOver.Broadcast();
}
