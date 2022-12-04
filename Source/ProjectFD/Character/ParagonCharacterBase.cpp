// Copyright ahnananananana. All Rights Reserved.

#include "ParagonCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterAbilitySetBase.h"
#include "../Player/ParagonPlayerState.h"
#include "../AI/ParagonAIControllerBase.h"
#include "../CustomMacros.h"
#include "Abilities/GameplayAbilityBase.h"
#include "ParagonMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"

AParagonCharacterBase::AParagonCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UParagonMovementComponent>(ACharacter::CharacterMovementComponentName))
	, bWasInputBindToAbilitySystem(false)
	, CurLocoState(ELocomotionState::Idle)
	, TurnSpeed(500)
	, PreviousYaw(0)
	, bIsSprint(false)
	, MoveYaw(0)
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	//TODO: SprintArm, CAmera ���� �־��
}

void AParagonCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	PreviousYaw = GetActorRotation().Yaw;

	m_pCamera = FindComponentByClass<UCameraComponent>();
}

void AParagonCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AParagonCharacterBase, CurLocoState);
	DOREPLIFETIME(AParagonCharacterBase, MoveYaw);

	//DOREPLIFETIME_CONDITION_NOTIFY(AParagonCharacterBase, CurLocoState, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(AParagonCharacterBase, MoveYaw, COND_None, REPNOTIFY_Always);
}

void AParagonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled())
	{
		return;
	}

	//TODO: �ӽ�
	SetLocomotionState(ELocomotionState::Idle);

	FVector CurFoward = GetActorForwardVector();
	CurFoward.Z = 0;
	CurFoward.Normalize();

	// ������ ȸ���� +, ������ -
	// 180�� �̻� ���̳��� +180/-180 ��踦 �������ٰ� �Ǵ�
	// ���� ��� ������ �ʹ� �����ϰ� ��ȿ����
	{
		double CurrentYaw = GetActorRotation().Yaw;
		if (!FMath::IsNearlyEqual(PreviousYaw, CurrentYaw))
		{
			double DeltaYaw = CurrentYaw - PreviousYaw;
			/*if ((0 < DeltaYaw && DeltaYaw < 180) || DeltaYaw < -180)
			{
				SetLocomotionState(ELocomotionState::Idle_Turn_Right);
			}
			else
			{
				SetLocomotionState(ELocomotionState::Idle_Turn_Left);
			}*/

			PreviousYaw = CurrentYaw;
		}
	}

	// �ܺ� �������� ���������� ���� �ű⼭ ���� ó���Ͽ� �����̴� ���°� ���� ���ϰ��ؾ�
	{
		UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		ENSURE(MoveComp);
		//Input�� Replication�� �ȵǹǷ� State�� ������
		if (MoveComp->GetLastInputVector() != FVector::ZeroVector)
		{
			// Forward ���Ϳ� �����̷��� ���� ������ ��
			double NewMoveYaw = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CurFoward, MoveComp->GetLastInputVector().GetSafeNormal())));
			// �����̷��� ���Ͱ� Foward ���� ���� �������� ���������� ���
			if (FVector::DotProduct(GetActorRightVector(), MoveComp->GetLastInputVector().GetSafeNormal()) < 0)
			{
				NewMoveYaw *= -1;
			}

			SetMoveYaw(NewMoveYaw);

			SetLocomotionState(ELocomotionState::Run);
			/*if (UAbilitySystemComponent* asc = GetAbilitySystemComponent())
			{
				if (asc->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Ability.Murdock.Sprint")))))
				{
					SetLocomotionState(ELocomotionState::Sprint);
				}
				else 
				{
					SetLocomotionState(ELocomotionState::Run);
				}
			}
			else
			{
				SetLocomotionState(ELocomotionState::Run);
			}*/
		}

		//// ���� �Է� ù �����ӿ� �����ؾ� �� �ڿ������� ������ ����
		//if (bPressedJump)
		//{
		//	SetLocomotionState(ELocomotionState::Jump);
		//}

		//if (MoveComp->IsFalling())
		//{
		//	SetLocomotionState(MoveComp->Velocity.Z > 0 ? ELocomotionState::Jump : ELocomotionState::Falling);
		//}
	}
}

void AParagonCharacterBase::SetMoveYaw_Implementation(double NewYaw)
{
	MoveYaw = NewYaw;
}

void AParagonCharacterBase::SetLocomotionState_Implementation(ELocomotionState NewState)
{
	if (CurLocoState == NewState)
	{
		return;
	}

	CurLocoState = NewState;
}

UAbilitySystemComponent* AParagonCharacterBase::GetAbilitySystemComponent() const
{
	if (AParagonPlayerState* ps = GetPlayerState<AParagonPlayerState>())
	{
		return ps->GetAbilitySystemComponent();
	}
	else if(AParagonAIControllerBase* ai = GetController<AParagonAIControllerBase>())
	{
		return ai->GetAbilitySystemComponent();
	}

	return nullptr;
}

void AParagonCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AParagonPlayerState* ps = GetPlayerState<AParagonPlayerState>())
	{
		if (UAbilitySystemComponent* AbilitySystemComp = ps->GetAbilitySystemComponent())
		{
			BindAbilitySystemToInputComponent(AbilitySystemComp);
		}
	}
}

void AParagonCharacterBase::LookToward(const FVector& TargetLook)
{
	TargetLookDir = TargetLook;
	TargetLookDir.Z = 0;
	TargetLookDir.Normalize();
}

void AParagonCharacterBase::LookAt(const FVector& TargetLookAt)
{
	LookToward(TargetLookAt - GetActorLocation());
}

//ASC �ʱ�ȭ ������
void AParagonCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeAbilitySystemComponent();
}

//ASC �ʱ�ȭ Ŭ���
void AParagonCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializeAbilitySystemComponent();
}

void AParagonCharacterBase::InitializeAbilitySystemComponent()
{
	UAbilitySystemComponent* AbilitySystemComp = nullptr;
	if (AParagonPlayerState* ps = GetPlayerState<AParagonPlayerState>())
	{
		AbilitySystemComp = ps->GetAbilitySystemComponent();
	}
	else if (AParagonAIControllerBase* ai = GetController<AParagonAIControllerBase>())
	{
		AbilitySystemComp = ai->GetAbilitySystemComponent();
	}

	ENSURE(AbilitySystemComp);

	AbilitySystemComp->SetAvatarActor(this);
	InitializeAttributes(AbilitySystemComp);
	InitializeAbilities(AbilitySystemComp);
	BindAbilitySystemToInputComponent(AbilitySystemComp);
}

void AParagonCharacterBase::InitializeAttributes(UAbilitySystemComponent* AbilitySystemComp)
{
	ENSURE(AbilitySystemComp);
	ENSURE(DefaultAttributeEffect);

	FGameplayEffectContextHandle EffectContext = AbilitySystemComp->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComp->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
	ENSURE(NewHandle.IsValid());

	FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
}

void AParagonCharacterBase::InitializeAbilities(UAbilitySystemComponent* AbilitySystemComp)
{
	ENSURE(AbilitySystemComp);
	//ENSURE(DefaultAbilities);

	if (HasAuthority())
	{
		AbilitySystemComp->ClearAllAbilities();
		//DefaultAbilities->GrantAbilities(AbilitySystemComp);

		for (TSubclassOf<UGameplayAbilityBase>& Ability : DefaultAbilities)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->GetInputID()), this));
		}
	}
}

void AParagonCharacterBase::BindAbilitySystemToInputComponent(UAbilitySystemComponent* AbilitySystemComp)
{
	ENSURE(AbilitySystemComp);

	if (!bWasInputBindToAbilitySystem && IsValid(InputComponent) && IsLocallyControlled())
	{
		//AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Confirm"), FString("Cancel"), FString("EAbilityInputID"), stat
		//AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds("", "", FString("EAbilityInputID")));
		
		AbilitySystemComp->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Confirm"),
			FString("Cancel"), FString("EAbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));

		bWasInputBindToAbilitySystem = true;
	}
}
