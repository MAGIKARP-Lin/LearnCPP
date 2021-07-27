// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
		class UButton* ContinueButton;

	UPROPERTY()
		class UButton* RestartButton;

	UPROPERTY()
		class UButton* ExitButton;
	
};
