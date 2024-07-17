// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_WidgetComponent.h"
#include "Base_Actor.h"

UBase_WidgetComponent::UBase_WidgetComponent()
{
	ABase_Actor* Base_Actor = Cast<ABase_Actor>(GetOwnerPlayer());

}
