// Copyright ahnananananana. All Rights Reserved.


#include "HeroCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "../../CustomMacros.h"
#include "../../Player/ParagonPlayerState.h"
#include "../../AI/Hero/HeroAIControllerBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"

AHeroCharacterBase::AHeroCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bWasInputBindToAbilitySystem(false)
	, MoveYaw(0)
	, Camera(nullptr)
{

	//TODO: SprintArm, CAmera 직접 넣어야
}

void AHeroCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHeroCharacterBase, MoveYaw);
}

void AHeroCharacterBase::SetMoveYaw_Implementation(double NewYaw)
{
	MoveYaw = NewYaw;
}

UAbilitySystemComponent* AHeroCharacterBase::GetAbilitySystemComponent() const
{
	if (AParagonPlayerState* ps = GetPlayerState<AParagonPlayerState>())
	{
		return ps->GetAbilitySystemComponent();
	}
	else if (AHeroAIControllerBase* ai = GetController<AHeroAIControllerBase>())
	{
		return ai->GetAbilitySystemComponent();
	}

	return nullptr;
}

//ASC 초기화 클라용
void AHeroCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializeAbilitySystemComponent();
}

void AHeroCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Camera = FindComponentByClass<UCameraComponent>();
}

void AHeroCharacterBase::SetDead()
{
	Super::SetDead();

	bUseControllerRotationYaw = false;
}

void AHeroCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void AHeroCharacterBase::InitializeAbilitySystemComponent()
{
	UAbilitySystemComponent* AbilitySystemComp = nullptr;
	if (AParagonPlayerState* ps = GetPlayerState<AParagonPlayerState>())
	{
		AbilitySystemComp = ps->GetAbilitySystemComponent();
	}
	else if (AHeroAIControllerBase* ai = GetController<AHeroAIControllerBase>())
	{
		AbilitySystemComp = ai->GetAbilitySystemComponent();
	}

	ENSURE(AbilitySystemComp);

	AbilitySystemComp->SetAvatarActor(this);
	InitializeAttributes(AbilitySystemComp);
	InitializeAbilities(AbilitySystemComp);
	BindAbilitySystemToInputComponent(AbilitySystemComp);
}

void AHeroCharacterBase::BindAbilitySystemToInputComponent(UAbilitySystemComponent* AbilitySystemComp)
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

void AHeroCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLocallyControlled())
	{
		return;
	}

	//TODO: 임시
	//SetLocomotionState(ELocomotionState::Idle);

	FVector CurFoward = GetActorForwardVector();
	CurFoward.Z = 0;
	CurFoward.Normalize();

	// 오른쪽 회전은 +, 왼쪽은 -
	// 180도 이상 차이나면 +180/-180 경계를 지나갔다고 판단
	// 벡터 기반 연산은 너무 복잡하고 비효율적
	//{
	//	double CurrentYaw = GetActorRotation().Yaw;
	//	if (!FMath::IsNearlyEqual(PreviousYaw, CurrentYaw))
	//	{
	//		double DeltaYaw = CurrentYaw - PreviousYaw;
	//		/*if ((0 < DeltaYaw && DeltaYaw < 180) || DeltaYaw < -180)
	//		{
	//			SetLocomotionState(ELocomotionState::Idle_Turn_Right);
	//		}
	//		else
	//		{
	//			SetLocomotionState(ELocomotionState::Idle_Turn_Left);
	//		}*/

	//		PreviousYaw = CurrentYaw;
	//	}
	//}

	// 외부 요인으로 움직여지는 것은 거기서 따로 처리하여 움직이는 상태가 되지 못하게해야
	{
		UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
		ENSURE(MoveComp);
		//Input은 Replication이 안되므로 State로 보내야
		if (MoveComp->GetLastInputVector() != FVector::ZeroVector)
		{
			// Forward 벡터와 움직이려는 벡터 사이의 각
			double NewMoveYaw = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CurFoward, MoveComp->GetLastInputVector().GetSafeNormal())));
			// 움직이려는 벡터가 Foward 벡터 기준 왼쪽인지 오른쪽인지 계산
			if (FVector::DotProduct(GetActorRightVector(), MoveComp->GetLastInputVector().GetSafeNormal()) < 0)
			{
				NewMoveYaw *= -1;
			}

			SetMoveYaw(NewMoveYaw);

			//SetLocomotionState(ELocomotionState::Run);
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

		//// 점프 입력 첫 프레임에 적용해야 더 자연스러운 블랜딩이 가능
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