// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"
class UProgressBar;//这种声明类的方式必须使用指针，因为指针不在乎你的内容是什么；如果使用头文件来定义，会影响编译速度
class UTextBlock;

/**
 * 
 */
UCLASS()
class LEARNCPP_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//绑定生命值
	UPROPERTY()
	UProgressBar* HealthBar;
	//绑定体力值
	UPROPERTY()
	UProgressBar* StaminaBar;
	//绑定击杀数
	UPROPERTY()
	UTextBlock* KilledText;
	//绑定子弹数
	UPROPERTY()
	UTextBlock* AmmoText;
	//绑定目标击杀数
	UPROPERTY()
	UTextBlock* TargetText;
};
