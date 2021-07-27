// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DoAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API UDoAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Key;

	UPROPERTY(EditAnywhere)
	float Damage;
};
