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
		//ApplyDamage 对指定角色造成伤害
		/*
		@param DamagedActor-将被损坏的Actor。
		@param BaseDamage-要应用的基础伤害。
		@param EventInstator-负责造成此损害的控制器(例如，射击武器的玩家)。
		@param DamageCauser-实际造成损害的演员(例如爆炸的手榴弹)。
		@param DamageTypeClass-描述造成的损害的类。
		@Return实际伤害最终应用于演员。
		*/
		//这个会自动调用指定角色的TakeDamage函数
		UGameplayStatics::ApplyDamage(Player, Damage, nullptr, nullptr, UDamageType::StaticClass());
	}

	return EBTNodeResult::Succeeded;
}
