// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ResetValue.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API UResetValue : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Key;

	UPROPERTY(EditAnywhere)
	AActor *Value;
};
