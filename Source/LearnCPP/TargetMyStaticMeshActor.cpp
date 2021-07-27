// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetMyStaticMeshActor.h"
#include "Engine/Engine.h"
#include "LearnCPPProjectile.h"
#include "LearnCPPCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

ATargetMyStaticMeshActor::ATargetMyStaticMeshActor()
{
	//让Tick运行
	PrimaryActorTick.bCanEverTick = true;
	Direction = FVector( 0, -10, 0);
	IsPrimed = false;
}

void ATargetMyStaticMeshActor::NotifyHitCallBack()
{
	UStaticMeshComponent* staticMash = GetStaticMeshComponent();
	if (staticMash)
	{
		//将物体变为原色的材质
		staticMash->SetMaterial(0, Original);
	}
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NotifyHitCallBack"));
}

void ATargetMyStaticMeshActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other == nullptr) return;

	//蓝图cast转换 ==> 类名 *指针 = Cast<类名>(要转换的对象)
	//子弹类 *projectile = Cast<子弹类>(Other);
	ALearnCPPProjectile *projectile = Cast<ALearnCPPProjectile>(Other);
	if (projectile != nullptr) 
	{
		//将获取蓝图的 Static Mesh Component
		UStaticMeshComponent *staticMash = GetStaticMeshComponent();

		if (staticMash)
		{
			//相当于蓝图的SetMaterial(将物体变为红色)
			//第一个参数为 给第几个元素添加材质
			//第二个参数为 要添加的材质
			staticMash->SetMaterial(0, TargetRed);
		}

		if (IsPrimed)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, HitLocation);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, HitLocation);
			ACharacter *character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (character)
			{
				ALearnCPPCharacter* learnCppCharacter =  Cast<ALearnCPPCharacter>(character);
				if (learnCppCharacter)
				{
					//击杀数+1
					learnCppCharacter->SetKilled(learnCppCharacter->GetKilled() + 1);
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
			IsPrimed = true;
			//设置Delay
			//这里LatentInfo是要与等完0.5秒后所要做的动作挂钩的
			FLatentActionInfo LatentInfo; 
			LatentInfo.Linkage = 0;
			//问哪个对象的Delay（要在谁身上执行该函数）
			LatentInfo.CallbackTarget = this;
			//执行的函数
			LatentInfo.ExecutionFunction = "NotifyHitCallBack";
			//__LINE__是代表当前的行号
			LatentInfo.UUID = __LINE__;
			UKismetSystemLibrary::Delay(GetWorld(), 0.5f, LatentInfo);
			//这样做后 相当于 0.5秒后做这个事情this->NotifyHitCallBack()
		}

	}

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NotifyHit"));
}

void ATargetMyStaticMeshActor::TickCallBack()
{
	Direction *= -1;
}

void ATargetMyStaticMeshActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//UKismetMathLibrary::Normal(Direction) 对向量进行归一化
	AddActorLocalOffset(UKismetMathLibrary::Normal(Direction) * DeltaSeconds * 200);

	FLatentActionInfo LatentInfo;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "TickCallBack";
	LatentInfo.UUID = __LINE__;
	UKismetSystemLibrary::Delay(GetWorld(), 3.0f, LatentInfo);
}
