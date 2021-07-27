// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"
class UProgressBar;//����������ķ�ʽ����ʹ��ָ�룬��Ϊָ�벻�ں����������ʲô�����ʹ��ͷ�ļ������壬��Ӱ������ٶ�
class UTextBlock;

/**
 * 
 */
UCLASS()
class LEARNCPP_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//������ֵ
	UPROPERTY()
	UProgressBar* HealthBar;
	//������ֵ
	UPROPERTY()
	UProgressBar* StaminaBar;
	//�󶨻�ɱ��
	UPROPERTY()
	UTextBlock* KilledText;
	//���ӵ���
	UPROPERTY()
	UTextBlock* AmmoText;
	//��Ŀ���ɱ��
	UPROPERTY()
	UTextBlock* TargetText;
};
