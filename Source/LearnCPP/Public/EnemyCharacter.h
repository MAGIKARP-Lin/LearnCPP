// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class LEARNCPP_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	//���õ�ǰѲ�ߵ�
	class ATargetPoint* CurrentPatrolPoint;

	//��ȡ�ڰ�
	class UBlackboardComponent* Blackboard;

	//�õ��˿������Ϳ�
	class UPawnSensingComponent* PawnSensing;

	////���ºڰ��еĸ��ٵ�
	//void UpdatePatrolPoint();

	//���������Ǻ�,���������õ��ڰ���
	UFUNCTION()
	void OnSeePawn(APawn *InPawn);

	//������������,��������λ�ü���ڰ�
	UFUNCTION()
	void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);

	//����ֵ
	int Health;
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	////�ڳ�����ָ��
	//UPROPERTY(EditInstanceOnly)
	//class ATargetPoint* PatrolPoint1;

	//UPROPERTY(EditInstanceOnly)
	//class ATargetPoint* PatrolPoint2;

	////����봥����������ײ
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//����ɱʱ���ŵ�����
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	USoundBase* ExplosionSound;

	//����ɱʱ����Ч
	UPROPERTY(EditDefaultsOnly, Category = "TargetSetting")
	UParticleSystem* ExplosionEffect;

	//��ײ����
	virtual void NotifyHit(
		class UPrimitiveComponent* MyComp, AActor* Other,
		class UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal,
		FVector NormalImpulse, const FHitResult& Hit)  override;
};