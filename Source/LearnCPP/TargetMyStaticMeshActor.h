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

	//声明一个判断是否被打中的变量
	bool IsPrimed;
public:
	//开放蓝图设置 之后会在细节对话框下面出现一个TargetSetting的分组
	//EditDefaultsOnly的意思是只能在蓝图里面更改，不能更改实例
	UPROPERTY(EditDefaultsOnly,Category="TargetSetting")
	UMaterialInterface* TargetRed;

	//EditAnywhere就是哪都能编辑
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UMaterialInterface* Original;

	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	USoundBase* ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UParticleSystem* ExplosionEffect;

	ATargetMyStaticMeshActor();

	//碰撞函数
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp, AActor* Other,
		class UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal,
		FVector NormalImpulse, const FHitResult& Hit)  override;

	virtual void Tick(float DeltaSeconds) override;
};
