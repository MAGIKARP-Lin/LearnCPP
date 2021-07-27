// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundTransWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API URoundTransWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	class UButton* StartButton;

	UPROPERTY()
	class UButton* ExitButton;

	UPROPERTY()
	class UTextBlock* RoundText;
};
