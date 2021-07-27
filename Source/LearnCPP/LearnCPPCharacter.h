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

	//�����ǿ��Է�������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnNoiseEmitterComponent* PawnNoiseEmitter;

	UMyUserWidget* HUD;
	URoundTransWidget* RoundTrans;
	ULoseMenuWidget* LoseMenu;
	UPauseMenuWidget* PauseMenu;

	int Ammo;
	int Killed;
	int Target;

	//������ʱ,ÿ����ķѵ�����
	float StaminaCost;
	bool IsSprinting;
	FTimerHandle SprintTimerHandle;

	//ֹͣ�����ܺ�,ÿ��ָ�������
	float StaminaRecharge;

	//�ж������Ƿ�ľ�
	UFUNCTION()
	void SprintDrain();

	UFUNCTION()
	void TickCallBack();

	//�Ƿ�����
	bool IsDeath;
public:
	ALearnCPPCharacter();

	//HUD����
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UMyUserWidget>WidgtClass;
	
	//WinMenu����
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<URoundTransWidget>RoundTransClass;

	//����ɱ����
	void SetKilled(int killed);
	//��ȡɱ����
	int GetKilled();

	//����ɱ����
	void SetTarget(int target);
	//��ȡɱ����
	int GetTarget();

	//�����ӵ���
	void SetAmmo(int ammo);
	int GetAmmo();

	//��Ϸ����
	void EndGame();

	//��ǰ��������
	int CurrentEnemyNumber;

	//LoseMenu����
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<ULoseMenuWidget> LoseMenuClass;

	//��ͣ����
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

	//����һ��������shift�����ܵĺ���
	void SprintBegin();
	//����һ���ɿ�shift�ͻع�ԭ���ٶȵĺ���
	void SprintStop();

	void ZoomBegin();
	void ZoomStop();

	//��Ϸ��ͣ
	void Pause();

	//����һ��������������
	UCurveFloat* FloatCurve;
	//����һ��ʱ����
	FTimeline ZoomTimeline;

	//����һ����ʱ��������ĺ���
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

	//�Ըý�ɫ����˺�
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void ReplayCallback();

	UFUNCTION()
	void ExitCallback();

	//�浵������
	FString SlotName;
	//�浵��ʵ��
	class USaveSystem* SaveInstance;

	UFUNCTION()
	void ContinueCallback();
	//����ͣ��������Ϸ
	UFUNCTION()
	void RestartFromPause();
};