// Fill out your copyright notice in the Description page of Project Settings.


#include "FindWanderTask.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFindWanderTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//获得一个导航系统 用来生成一个随机的巡逻位置
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	//新生成的巡逻点
	FNavLocation WanderPoint;

	if (NavigationSystem->GetRandomReachablePointInRadius(
		OwnerComp.GetOwner()->GetActorLocation(), 10000, WanderPoint))
	{
		//OwnerComp.GetBlackboardComponent() 获得黑板
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Key.SelectedKeyName, WanderPoint.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
