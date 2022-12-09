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

	//TODO: SprintArm, CAmera ���� �־��
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

//ASC �ʱ�ȭ Ŭ���
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

	//TODO: �ӽ�
	//SetLocomotionState(ELocomotionState::Idle);

	FVector CurFoward = GetActorForwardVector();
	CurFoward.Z = 0;
	CurFoward.Normalize();

	// ������ ȸ���� +, ������ -
	// 180�� �̻� ���̳��� +180/-180 ��踦 �������ٰ� �Ǵ�
	// ���� ��� ������ �ʹ� �����ϰ� ��ȿ����
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