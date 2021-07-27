  // Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "LearnCPPCharacter.generated.h"

class UInputComponent;
class UMyUserWidget;
class URoundTransWidget;
class ULoseMenuWidget;
class UPauseMenuWidget;

UCLASS(config=Game)
class ALearnCPPCharacter : public ACharacter
{	
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

	//让主角可以发出声音
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnNoiseEmitterComponent* PawnNoiseEmitter;

	UMyUserWidget* HUD;
	URoundTransWidget* RoundTrans;
	ULoseMenuWidget* LoseMenu;
	UPauseMenuWidget* PauseMenu;

	int Ammo;
	int Killed;
	int Target;

	//加速跑时,每秒需耗费的体力
	float StaminaCost;
	bool IsSprinting;
	FTimerHandle SprintTimerHandle;

	//停止加速跑后,每秒恢复的体力
	float StaminaRecharge;

	//判断体力是否耗尽
	UFUNCTION()
	void SprintDrain();

	UFUNCTION()
	void TickCallBack();

	//是否死亡
	bool IsDeath;
public:
	ALearnCPPCharacter();

	//HUD界面
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UMyUserWidget>WidgtClass;
	
	//WinMenu界面
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<URoundTransWidget>RoundTransClass;

	//设置杀敌数
	void SetKilled(int killed);
	//获取杀敌数
	int GetKilled();

	//设置杀敌数
	void SetTarget(int target);
	//获取杀敌数
	int GetTarget();

	//设置子弹数
	void SetAmmo(int ammo);
	int GetAmmo();

	//游戏结束
	void EndGame();

	//当前敌人数量
	int CurrentEnemyNumber;

	//LoseMenu界面
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<ULoseMenuWidget> LoseMenuClass;

	//暂停界面
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UPauseMenuWidget> PauseMenuClass;
protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ALearnCPPProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//声明一个当按下shift加速跑的函数
	void SprintBegin();
	//声明一个松开shift就回归原来速度的函数
	void SprintStop();

	void ZoomBegin();
	void ZoomStop();

	//游戏暂停
	void Pause();

	//声明一个浮点数的曲线
	UCurveFloat* FloatCurve;
	//声明一个时间线
	FTimeline ZoomTimeline;

	//声明一个做时间线事情的函数
	UFUNCTION()
	void DoZoom(float FieldOfView);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void Tick(float DeltaSeconds) override;

	//对该角色造成伤害
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ReplayCallback();

	UFUNCTION()
	void ExitCallback();

	//存档的名字
	FString SlotName;
	//存档的实例
	class USaveSystem* SaveInstance;

	UFUNCTION()
	void ContinueCallback();
	//在暂停中重置游戏
	UFUNCTION()
	void RestartFromPause();
};