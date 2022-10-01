
#include "GameBaseCharacter.h"
#include "Curves/CurveFloat.h"
#include "HelperMacro.h"
#include "AbilitySystemComponentBase.h"
#include "HealthComponent.h"
#include "GameCharacterAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameBaseCharacter::AGameBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pAbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponentBase>("Ability System Component");
	m_pAbilitySystemComp->SetIsReplicated(true);
	m_pAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AGameBaseCharacter::BindInputAbility(const EInput& _eInput, const TSubclassOf<UGameplayAbilityBase>& _Ability)
{
	m_mapInputAbility.Emplace(_eInput, _Ability);
}

// Called when the game starts or when spawned
void AGameBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_pCharacterData = m_BaseData.GetRow<FCharacterData>(TEXT(""));

	// Init Gameplay Ability System
	{
		//TODO: Attribute 쪽에서 초기화하는 방법은 없나? 여기서 하는게 가독성이 더 좋은가?
		m_pAbilitySystemComp->InitAttribute(m_BaseData);
		
		for (const FAbilityInitInfo& info : m_arrDefaultAbilities)
		{
			m_pAbilitySystemComp->GiveAbility(FGameplayAbilitySpec(info.Ability));
			
			if (info.Input != EInput::NONE)
			{
				BindInputAbility(info.Input, info.Ability);
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

// Called every frame
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

	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		if (pc->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			m_pAbilitySystemComp->TryActivateAbilityByClass(m_mapInputAbility[EInput::PRIMARY_ACTION]);
		}
		else if (pc->WasInputKeyJustPressed(EKeys::RightMouseButton))
		{
			m_pAbilitySystemComp->TryActivateAbilityByClass(m_mapInputAbility[EInput::SECONDARY_ACTION]);
		}
		else if (pc->WasInputKeyJustReleased(EKeys::RightMouseButton))
		{
			m_pAbilitySystemComp->CancelAbility(m_mapInputAbility[EInput::SECONDARY_ACTION].GetDefaultObject());
		}
		else if (pc->WasInputKeyJustPressed(EKeys::Q))
		{
			m_pAbilitySystemComp->TryActivateAbilityByClass(m_mapInputAbility[EInput::SKILL1]);
		}
		else if (pc->WasInputKeyJustPressed(EKeys::E))
		{
			m_pAbilitySystemComp->TryActivateAbilityByClass(m_mapInputAbility[EInput::SKILL2]);
		}
		else if (pc->WasInputKeyJustPressed(EKeys::R))
		{
			m_pAbilitySystemComp->TryActivateAbilityByClass(m_mapInputAbility[EInput::ULTIMATE]);
		}
	}	 
		
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

