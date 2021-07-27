// Fill out your copyright notice in the Description page of Project Settings.


#include "FindWanderTask.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFindWanderTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//���һ������ϵͳ ��������һ�������Ѳ��λ��
	UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	//�����ɵ�Ѳ�ߵ�
	FNavLocation WanderPoint;

	if (NavigationSystem->GetRandomReachablePointInRadius(
		OwnerComp.GetOwner()->GetActorLocation(), 10000, WanderPoint))
	{
		//OwnerComp.GetBlackboardComponent() ��úڰ�
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Key.SelectedKeyName, WanderPoint.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
