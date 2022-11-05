
#include "GameBaseCharacter.h"
#include "Curves/CurveFloat.h"
#include "HelperMacro.h"
#include "AbilitySystemComponentBase.h"
#include "PlayerCharacterAbility.h"
#include "GameCharacterAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

// Sets default values
AGameBaseCharacter::AGameBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pAbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponentBase>("Ability System Component");
	m_pAbilitySystemComp->SetIsReplicated(true);
	m_pAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	m_pAttributeSet = CreateDefaultSubobject<UGameCharacterAttributeSet>("AttributeSet");

	m_arrBindedAbilities.SetNum((int)EInput::count);
}

void AGameBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameBaseCharacter, m_arrBindedAbilities);
}

void AGameBaseCharacter::BindInputAbility(const EInput& _eInput, const FGameplayAbilitySpecHandle& _Handle)
{
	//m_mapInputAbility.Emplace(_eInput, _Handle);
	m_arrBindedAbilities[(int)_eInput] = _Handle;
}

// Called when the game starts or when spawned
void AGameBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		m_pCharacterData = m_BaseData.GetRow<FCharacterData>(TEXT(""));

		// Init Gameplay Ability System
		{
			//TODO: Attribute 쪽에서 초기화하는 방법은 없나? 여기서 하는게 가독성이 더 좋은가?
			m_pAttributeSet->Init(m_BaseData);

			for (const FAbilityInitInfo& info : m_arrDefaultAbilities)
			{
				FGameplayAbilitySpecHandle handle = m_pAbilitySystemComp->GiveAbility(FGameplayAbilitySpec(info.Ability));

				if (info.Input != EInput::NONE)
				{
					BindInputAbility(info.Input, handle);
				}
			}
		}
	}
}



UAbilitySystemComponent* AGameBaseCharacter::GetAbilitySystemComponent() const
{
	return m_pAbilitySystemComp;
}

FVector AGameBaseCharacter::GetAimPoint() const
{
	if (IsPlayerControlled())
	{
		FHitResult result;
		
		FVector vStart, vEnd;
		FRotator rRot;
		Cast<APlayerController>(GetController())->GetPlayerViewPoint(vStart, rRot);
		vEnd = vStart + 99999 * rRot.Vector();

		if (GetWorld()->LineTraceSingleByChannel(result, vStart, vEnd, ECollisionChannel::ECC_Visibility))
		{
			DrawDebugSphere(GetWorld(), result.ImpactPoint, 10, 32, FColor::Red);
			return result.ImpactPoint;
		}

		return vEnd;
	}
	else
	{
		return GetActorForwardVector();
	}
}

void AGameBaseCharacter::ActivateAbility_Implementation(const EInput& _eType)
{
	UE_LOG(LogTemp, Log, TEXT("ActivateAbility_Implementation %d"), GetWorld()->IsServer());
	m_pAbilitySystemComp->TryActivateAbility(m_arrBindedAbilities[(int)_eType]);
}

void AGameBaseCharacter::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);

	//LookRotation 계산
	{
		m_rLookRotation = GetViewRotation() - GetActorRotation();

		if(m_rLookRotation.Pitch > 180)
			m_rLookRotation.Pitch -= 360;

		if (m_rLookRotation.Yaw > 180)
			m_rLookRotation.Yaw -= 360;
	}

	/*if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		if (m_mapInputAbility.Contains(EInput::PRIMARY_ACTION) && pc->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::PRIMARY_ACTION]);
		}
		else if (m_mapInputAbility.Contains(EInput::SECONDARY_ACTION) && pc->WasInputKeyJustPressed(EKeys::RightMouseButton))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::SECONDARY_ACTION]);
		}
		else if (m_mapInputAbility.Contains(EInput::SECONDARY_ACTION) && pc->WasInputKeyJustReleased(EKeys::RightMouseButton))
		{
			m_pAbilitySystemComp->CancelAbilityHandle(m_mapInputAbility[EInput::SECONDARY_ACTION]);
		}
		else if (m_mapInputAbility.Contains(EInput::SKILL1) && pc->WasInputKeyJustPressed(EKeys::Q))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::SKILL1]);
		}
		else if (m_mapInputAbility.Contains(EInput::SKILL2) && pc->WasInputKeyJustPressed(EKeys::E))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::SKILL2]);
		}
		else if (m_mapInputAbility.Contains(EInput::ULTIMATE) && pc->WasInputKeyJustPressed(EKeys::R))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::ULTIMATE]);
		}
		
		if (m_testEffect.Get() && pc->WasInputKeyJustPressed(EKeys::T))
		{
			FGameplayEffectContextHandle h;
			m_pAbilitySystemComp->ApplyGameplayEffectToSelf(m_testEffect.GetDefaultObject(), 1, h);
		}
	}	 */
		
	////LookRotation의 Yaw가 90이나 -90을 넘어가면 그 방향으로 회전
	//{
	//	if (m_rLookRotation.Yaw < -90)
	//	{
	//		Turn(-90);
	//	}
	//	else if (m_rLookRotation.Yaw > 90)
	//	{
	//		Turn(90);
	//	}
	//}

	////Turn 처리
	//{
	//	if (m_bIsTurning)
	//	{
	//		float fMinTime, fMaxTime;
	//		m_pTurnCurve->GetTimeRange(fMinTime, fMaxTime);
	//		float fDelta = GetWorld()->GetTimeSeconds() - m_fTurnStartTime;
	//		float fTime = fDelta / (fMaxTime - fMinTime);
	//		float fWeight = m_pTurnCurve->GetFloatValue(fTime);

	//		FQuat4d rCurRot = GetActorRotation().Quaternion();
	//		rCurRot = FQuat4d::Slerp(rCurRot, m_qTargetRot, fWeight);
	//		SetActorRotation(rCurRot);
	//		if (fTime >= 1.f)
	//		{
	//			m_bIsTurning = false;
	//		}
	//	}
	//}
}

//void AGameBaseCharacter::Turn(double _dAngle)
//{
//	if(m_bIsTurning)
//		return;
//
//	LOG("turn");
//	FRotator rCurRot = GetActorRotation();
//	rCurRot.Yaw += _dAngle;
//	m_qTargetRot = rCurRot.Quaternion();
//	m_fTurnStartTime = GetWorld()->GetTimeSeconds();
//	m_bIsTurning = true;
//}

