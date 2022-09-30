
#include "GameBaseCharacter.h"
#include "Curves/CurveFloat.h"
#include "HelperMacro.h"
#include "AbilitySystemComponentBase.h"
#include "HealthComponent.h"
#include "GameCharacterAttributeSet.h"

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

void AGameBaseCharacter::BindInputAbility(const EInput& _eInput, const FGameplayAbilitySpecHandle& _Handle)
{
	m_mapInputAbility.Emplace(_eInput, _Handle);
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
		
		for (const FAbilityInitInfo& info : m_arrInitialAbilities)
		{
			FGameplayAbilitySpec spec = info.AbilityInfo.CreateInstance(this);

			FGameplayAbilitySpecHandle handle = m_pAbilitySystemComp->GiveAbility(spec);

			if (info.Input != EInput::NONE)
			{
				BindInputAbility(info.Input, handle);
			}
		}
	}
}

UAbilitySystemComponent* AGameBaseCharacter::GetAbilitySystemComponent() const
{
	return m_pAbilitySystemComp;
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
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::PRIMARY_ACTION]);
		}
		else if (pc->WasInputKeyJustPressed(EKeys::RightMouseButton))
		{
			m_pAbilitySystemComp->TryActivateAbility(m_mapInputAbility[EInput::SECONDARY_ACTION]);
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

