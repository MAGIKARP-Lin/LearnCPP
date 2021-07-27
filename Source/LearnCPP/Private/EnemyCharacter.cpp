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
	//设置敌人的视角
	PawnSensing->SetPeripheralVisionAngle(60);
	//设置听力的范围
	//无遮挡 听到的最大距离
	PawnSensing->HearingThreshold = 1400;
	//有遮挡 听到的最大距离
	PawnSensing->LOSHearingThreshold = 1400;

	Health = 3;
}
//
//void AEnemyCharacter::UpdatePatrolPoint()
//{
//	if (Blackboard)
//	{
//		//将当前目标点设置到黑板中去
//		Blackboard->SetValueAsObject("PatrolPoint", CurrentPatrolPoint);
//	}
//}

void AEnemyCharacter::OnSeePawn(APawn* InPawn)
{
	//判断看到的是否是主角
	if (Cast<ALearnCPPCharacter>(InPawn))
	{
		if (!Blackboard)
		{
			Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
		}
		//如果是主角
		if (Blackboard)
		{
			//将当前目标点设置到黑板的Player中
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
		//进当前声音的位置设置到黑板中
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
		//当看到主角后,将主角添加到黑板中
		//OnSeePawn是一个委托函数  
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
//	//判断碰撞的点是否是目标点
//	ATargetPoint* Point = Cast<ATargetPoint>(OtherActor);
//
//	//如果存在，则是目标点
//	if (Point)
//	{
//		//判断该点是否是第一个跟踪点
//		if (Point == PatrolPoint1)
//		{
//			//切换目标点
//			CurrentPatrolPoint = PatrolPoint2;
//		}
//		//判断该点是否是第二个跟踪点
//		else if (Point == PatrolPoint2)
//		{
//			//切换目标点
//			CurrentPatrolPoint = PatrolPoint1;
//		}
//		UpdatePatrolPoint();
//	}
//}

void AEnemyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other == nullptr) return;

	//蓝图cast转换 ==> 类名 *指针 = Cast<类名>(要转换的对象)
	//子弹类 *projectile = Cast<子弹类>(Other);
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
					//击杀数+1
					learnCppCharacter->SetKilled(learnCppCharacter->GetKilled() + 1);
					//场上敌人数-1 且不能小于0
					--learnCppCharacter->CurrentEnemyNumber;
					if (learnCppCharacter->CurrentEnemyNumber < 0)
					{
						learnCppCharacter->CurrentEnemyNumber = 0;
					}
					//当击杀数 >= 目标击杀数
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

