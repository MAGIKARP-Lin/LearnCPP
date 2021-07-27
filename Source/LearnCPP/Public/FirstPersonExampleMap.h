// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "FirstPersonExampleMap.generated.h"

/**
 * 
 */
UCLASS()
class LEARNCPP_API AFirstPersonExampleMap : public ALevelScriptActor
{
	GENERATED_BODY()
	
	//行为树
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	//生成点
	UPROPERTY(EditDefaultsOnly)
	class ATargetPoint* SpawnPoint;

	//生成的类型(因为敌人就是APawn的子类)
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PawnClass;

	FTimerHandle PawnTimerHandle;
public:
	UFUNCTION()
	void Spawn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
