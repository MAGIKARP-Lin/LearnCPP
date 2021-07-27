// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetValue.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UResetValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//OwnerComp.GetBlackboardComponent() ��úڰ�
	//������� ���ڰ���Player��ֵ�����
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Key.SelectedKeyName,Value);
	return EBTNodeResult::Succeeded;
}
