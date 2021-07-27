// Fill out your copyright notice in the Description page of Project Settings.


#include "DoAttackTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

EBTNodeResult::Type UDoAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Key.SelectedKeyName));

	if (Player)
	{
		//ApplyDamage ��ָ����ɫ����˺�
		/*
		@param DamagedActor-�����𻵵�Actor��
		@param BaseDamage-ҪӦ�õĻ����˺���
		@param EventInstator-������ɴ��𺦵Ŀ�����(���磬������������)��
		@param DamageCauser-ʵ������𺦵���Ա(���籬ը������)��
		@param DamageTypeClass-������ɵ��𺦵��ࡣ
		@Returnʵ���˺�����Ӧ������Ա��
		*/
		//������Զ�����ָ����ɫ��TakeDamage����
		UGameplayStatics::ApplyDamage(Player, Damage, nullptr, nullptr, UDamageType::StaticClass());
	}

	return EBTNodeResult::Succeeded;
}
