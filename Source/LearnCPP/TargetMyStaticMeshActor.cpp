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
	//��Tick����
	PrimaryActorTick.bCanEverTick = true;
	Direction = FVector( 0, -10, 0);
	IsPrimed = false;
}

void ATargetMyStaticMeshActor::NotifyHitCallBack()
{
	UStaticMeshComponent* staticMash = GetStaticMeshComponent();
	if (staticMash)
	{
		//�������Ϊԭɫ�Ĳ���
		staticMash->SetMaterial(0, Original);
	}
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NotifyHitCallBack"));
}

void ATargetMyStaticMeshActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (Other == nullptr) return;

	//��ͼcastת�� ==> ���� *ָ�� = Cast<����>(Ҫת���Ķ���)
	//�ӵ��� *projectile = Cast<�ӵ���>(Other);
	ALearnCPPProjectile *projectile = Cast<ALearnCPPProjectile>(Other);
	if (projectile != nullptr) 
	{
		//����ȡ��ͼ�� Static Mesh Component
		UStaticMeshComponent *staticMash = GetStaticMeshComponent();

		if (staticMash)
		{
			//�൱����ͼ��SetMaterial(�������Ϊ��ɫ)
			//��һ������Ϊ ���ڼ���Ԫ����Ӳ���
			//�ڶ�������Ϊ Ҫ��ӵĲ���
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
					//��ɱ��+1
					learnCppCharacter->SetKilled(learnCppCharacter->GetKilled() + 1);
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
			IsPrimed = true;
			//����Delay
			//����LatentInfo��Ҫ�����0.5�����Ҫ���Ķ����ҹ���
			FLatentActionInfo LatentInfo; 
			LatentInfo.Linkage = 0;
			//���ĸ������Delay��Ҫ��˭����ִ�иú�����
			LatentInfo.CallbackTarget = this;
			//ִ�еĺ���
			LatentInfo.ExecutionFunction = "NotifyHitCallBack";
			//__LINE__�Ǵ���ǰ���к�
			LatentInfo.UUID = __LINE__;
			UKismetSystemLibrary::Delay(GetWorld(), 0.5f, LatentInfo);
			//�������� �൱�� 0.5������������this->NotifyHitCallBack()
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
	//UKismetMathLibrary::Normal(Direction) ���������й�һ��
	AddActorLocalOffset(UKismetMathLibrary::Normal(Direction) * DeltaSeconds * 200);

	FLatentActionInfo LatentInfo;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "TickCallBack";
	LatentInfo.UUID = __LINE__;
	UKismetSystemLibrary::Delay(GetWorld(), 3.0f, LatentInfo);
}
