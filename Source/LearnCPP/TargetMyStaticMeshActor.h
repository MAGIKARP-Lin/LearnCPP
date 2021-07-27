// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TargetMyStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API ATargetMyStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

	UFUNCTION()
	void NotifyHitCallBack();

	UFUNCTION()
	void TickCallBack();

	FVector Direction;

	//����һ���ж��Ƿ񱻴��еı���
	bool IsPrimed;
public:
	//������ͼ���� ֮�����ϸ�ڶԻ����������һ��TargetSetting�ķ���
	//EditDefaultsOnly����˼��ֻ������ͼ������ģ����ܸ���ʵ��
	UPROPERTY(EditDefaultsOnly,Category="TargetSetting")
	UMaterialInterface* TargetRed;

	//EditAnywhere�����Ķ��ܱ༭
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UMaterialInterface* Original;

	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UParticleSystem* ExplosionEffect;

	ATargetMyStaticMeshActor();

	//��ײ����
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp, AActor* Other,
		class UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal,
		FVector NormalImpulse, const FHitResult& Hit)  override;

	virtual void Tick(float DeltaSeconds) override;
};
