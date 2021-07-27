// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class LEARNCPP_API AEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
};
