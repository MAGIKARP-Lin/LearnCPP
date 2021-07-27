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
	
	//��Ϊ��
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTree;

	//���ɵ�
	UPROPERTY(EditDefaultsOnly)
	class ATargetPoint* SpawnPoint;

	//���ɵ�����(��Ϊ���˾���APawn������)
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
