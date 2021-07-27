// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "LearnCPP/LearnCPPCharacter.h"
#include "LearnCPP/LearnCPPProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");
	//���õ��˵��ӽ�
	PawnSensing->SetPeripheralVisionAngle(60);
	//���������ķ�Χ
	//���ڵ� ������������
	PawnSensing->HearingThreshold = 1400;
	//���ڵ� ������������
	PawnSensing->LOSHearingThreshold = 1400;

	Health = 3;
}
//
//void AEnemyCharacter::UpdatePatrolPoint()
//{
//	if (Blackboard)
//	{
//		//����ǰĿ������õ��ڰ���ȥ
//		Blackboard->SetValueAsObject("PatrolPoint", CurrentPatrolPoint);
//	}
//}

void AEnemyCharacter::OnSeePawn(APawn* InPawn)
{
	//�жϿ������Ƿ�������
	if (Cast<ALearnCPPCharacter>(InPawn))
	{
		if (!Blackboard)
		{
			Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
		}
		//���������
		if (Blackboard)
		{
			//����ǰĿ������õ��ڰ��Player��
			Blackboard->SetValueAsObject("Player", InPawn);
		}
	}
}

void AEnemyCharacter::OnHearNoise(APawn* Pawn, const FVector& Location, float Volume)
{
	if (!Blackboard)
	{
		Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	}
	if (Blackboard)
	{
		//����ǰ������λ�����õ��ڰ���
		Blackboard->SetValueAsVector("PlayerLocation", Location);
		Blackboard->SetValueAsBool("IsHeardPlayer", true);
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensing)
	{
		//���������Ǻ�,��������ӵ��ڰ���
		//OnSeePawn��һ��ί�к���  
		//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FSeePawnDelegate, APawn*, Pawn );
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
		PawnSensing->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnHearNoise);
	}

	Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);

	//CurrentPatrolPoint = PatrolPoint1;
	//UpdatePatrolPoint();
}

//
//void AEnemyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	//�ж���ײ�ĵ��Ƿ���Ŀ���
//	ATargetPoint* Point = Cast<ATargetPoint>(OtherActor);
//
//	//������ڣ�����Ŀ���
//	if (Point)
//	{
//		//�жϸõ��Ƿ��ǵ�һ�����ٵ�
//		if (Point == PatrolPoint1)
//		{
//			//�л�Ŀ���
//			CurrentPatrolPoint = PatrolPoint2;
//		}
//		//�жϸõ��Ƿ��ǵڶ������ٵ�
//		else if (Point == PatrolPoint2)
//		{
//			//�л�Ŀ���
//			CurrentPatrolPoint = PatrolPoint1;
//		}
//		UpdatePatrolPoint();
//	}
//}

void AEnemyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other == nullptr) return;

	//��ͼcastת�� ==> ���� *ָ�� = Cast<����>(Ҫת���Ķ���)
	//�ӵ��� *projectile = Cast<�ӵ���>(Other);
	ALearnCPPProjectile* projectile = Cast<ALearnCPPProjectile>(Other);
	if (projectile != nullptr)
	{
		if (Health == 1)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, HitLocation);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, HitLocation);
			ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (character)
			{
				ALearnCPPCharacter* learnCppCharacter = Cast<ALearnCPPCharacter>(character);
				if (learnCppCharacter)
				{
					//��ɱ��+1
					learnCppCharacter->SetKilled(learnCppCharacter->GetKilled() + 1);
					//���ϵ�����-1 �Ҳ���С��0
					--learnCppCharacter->CurrentEnemyNumber;
					if (learnCppCharacter->CurrentEnemyNumber < 0)
					{
						learnCppCharacter->CurrentEnemyNumber = 0;
					}
					//����ɱ�� >= Ŀ���ɱ��
					if (learnCppCharacter->GetKilled() >= learnCppCharacter->GetTarget())
					{
						learnCppCharacter->EndGame();
					}
				}
			}
			Destroy();
		}
		else
		{
			--Health;
		}
	}
}

