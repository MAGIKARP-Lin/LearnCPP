// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class LEARNCPP_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	//设置当前巡逻点
	class ATargetPoint* CurrentPatrolPoint;

	//获取黑板
	class UBlackboardComponent* Blackboard;

	//让敌人可以听和看
	class UPawnSensingComponent* PawnSensing;

	////更新黑板中的跟踪点
	//void UpdatePatrolPoint();

	//当看到主角后,将主角设置到黑板中
	UFUNCTION()
	void OnSeePawn(APawn *InPawn);

	//当听到声音后,将声音的位置加入黑板
	UFUNCTION()
	void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);

	//体力值
	int Health;
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	////在场景中指定
	//UPROPERTY(EditInstanceOnly)
	//class ATargetPoint* PatrolPoint1;

	//UPROPERTY(EditInstanceOnly)
	//class ATargetPoint* PatrolPoint2;

	////玩家与触发器发生碰撞
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//被击杀时播放的声音
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	USoundBase* ExplosionSound;

	//被击杀时的特效
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UParticleSystem* ExplosionEffect;

	//碰撞函数
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp, AActor* Other,
		class UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal,
		FVector NormalImpulse, const FHitResult& Hit)  override;
};