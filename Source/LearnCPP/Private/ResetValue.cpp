// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetValue.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UResetValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//OwnerComp.GetBlackboardComponent() 获得黑板
	//忘记玩家 将黑板中Player的值给清空
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Key.SelectedKeyName,Value);
	return EBTNodeResult::Succeeded;
}
