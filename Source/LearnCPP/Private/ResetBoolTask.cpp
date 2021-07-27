// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetBoolTask.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UResetBoolTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//OwnerComp.GetBlackboardComponent() »ñµÃºÚ°å
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(Key.SelectedKeyName, Value);
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UResetBoolTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(Key.SelectedKeyName, Value);
	return EBTNodeResult::Succeeded;
}
