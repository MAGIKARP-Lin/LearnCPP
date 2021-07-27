// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoseMenuWidget.generated.h"
class UButton;
/**
 * 
 */
UCLASS()
class LEARNCPP_API ULoseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UButton* ReplayButton;

	UPROPERTY()
	UButton* ExitButton;

};
