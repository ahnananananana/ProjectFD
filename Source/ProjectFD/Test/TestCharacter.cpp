#include "TestCharacter.h"
#include "TestAttributeSet.h"
#include "TestAbilitySystemComponent.h"
#include "TestPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "../CustomMacros.h"
#include "GameFramework/GameStateBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameModeBase.h"
//void StaticTest()
//{
//	UE_LOG(LogTemp, Log, TEXT("static"));
//}
//
//// Sets default values
//ATestCharacter::ATestCharacter()
//{
// 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//}
//
//// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	s1 = FindComponentByClass<USphereComponent>();
	s2 = FindComponentByClass<USphereComponent>();
	s3 = FindComponentByClass<USphereComponent>();
	s4 = FindComponentByClass<USphereComponent>();
	s5 = FindComponentByClass<USphereComponent>();
	s6 = FindComponentByClass<USphereComponent>();
}
//
//void ATestCharacter::Test()
//{
//	++aa;
//}
//
//void ATestCharacter::Test2()
//{
//	++aa;
//}
//
//// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (World->GetAuthGameMode()->GetGameState<AGameStateBase>()->GetClass() == GameStateClass1)
	{
		UE_LOG(LogTemp, Log, TEXT("Test"));
	}

	if (auto p = GetController<APlayerController>())
	{
		if (p->WasInputKeyJustPressed(EKeys::R))
		{
			if (s1)
			{
				UE_LOG(LogTemp, Log, TEXT("s1"));
			}
			if (s2)
			{
				UE_LOG(LogTemp, Log, TEXT("s2"));
			}
			if (s3.Get())
			{
				UE_LOG(LogTemp, Log, TEXT("s3"));
			}
			if (s4.Get())
			{
				UE_LOG(LogTemp, Log, TEXT("s4"));
			}

			//FActorSpawnParameters SpawnInfo;
			//SpawnInfo.Instigator = GetInstigator();
			//SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save game states or network managers into a map									

			//TSubclassOf<AGameStateBase> GameStateClass = World->GetGameState()->GetClass() == GameStateClass1 ? GameStateClass2 : GameStateClass1;
			//auto GameState = World->SpawnActor<AGameStateBase>(GameStateClass, SpawnInfo);
			//World->SetGameState(GameState);
			
			/*ATestPlayerState* pPS = GetPlayerState<ATestPlayerState>();
			UAbilitySystemComponent* pASC = pPS->GetAbilitySystemComponent();

			FGameplayEffectContextHandle EffectContext = pASC->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = pASC->MakeOutgoingSpec(TestEffect, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = pASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
			}*/
			/*FDateTime start = FDateTime::UtcNow();
			del1.Broadcast();
			UE_LOG(LogTemp, Log, TEXT("%d"), FDateTime::UtcNow().GetTicks() - start.GetTicks());
			start = FDateTime::UtcNow();
			del2.Broadcast();
			UE_LOG(LogTemp, Log, TEXT("%d"), FDateTime::UtcNow().GetTicks() - start.GetTicks());*/
		}
	}
	/*if (GetController<APlayerController>()->WasInputKeyJustPressed(EKeys::R))
	{
		ATestPlayerState* pPS = GetPlayerState<ATestPlayerState>();
		UAbilitySystemComponent* pASC = pPS->GetAbilitySystemComponent();

		FGameplayEffectContextHandle EffectContext = pASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = pASC->MakeOutgoingSpec(TestEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = pASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}
	if (GetController<APlayerController>()->WasInputKeyJustPressed(EKeys::E))
	{
		ATestPlayerState* pPS = GetPlayerState<ATestPlayerState>();
		UAbilitySystemComponent* pASC = pPS->GetAbilitySystemComponent();

		FGameplayEffectContextHandle EffectContext = pASC->MakeEffectContext();
		EffectContext.AddSourceObject(pPS);

		FGameplayEffectSpecHandle NewHandle = pASC->MakeOutgoingSpec(TestEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = pASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}*/
}
//
//void ATestCharacter::BindAbilitySystemToInputComponent()
//{
//	if (ATestPlayerState* pPS = GetPlayerState<ATestPlayerState>())
//	{
//		if (UAbilitySystemComponent* pASC = pPS->GetAbilitySystemComponent())
//		{
//			if (InputComponent)
//			{
//				//pASC->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Confirm"), FString("Cancel"), FString("EAbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
//				pASC->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds("", "", FString("EAbilityInputID")));
//			}
//		}
//	}
//}
//void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	BindAbilitySystemToInputComponent();
//}
//
////ASC 초기화 서버용
//void ATestCharacter::PossessedBy(AController* NewController)
//{
//	Super::PossessedBy(NewController);
//
//	InitializeAbilitySystemComponent();
//}
//
////ASC 초기화 클라용
//void ATestCharacter::OnRep_PlayerState()
//{
//	Super::OnRep_PlayerState();
//
//	InitializeAbilitySystemComponent();
//}
//
//void ATestCharacter::InitializeAbilitySystemComponent()
//{
//	ATestPlayerState* pPS = GetPlayerState<ATestPlayerState>();
//	ENSURE(pPS);
//
//	UAbilitySystemComponent* pASC = pPS->GetAbilitySystemComponent();
//	ENSURE(pASC);
//
//	pASC->SetAvatarActor(this);
//
//	InitializeAttributes(pASC, DefaultAttributes);
//
//	if (HasAuthority())
//	{
//		pASC->ClearAllAbilities();
//		for (FAbilityBindInfo& info : DefaultAbilities)
//		{
//			pASC->GiveAbility(FGameplayAbilitySpec(info.AbilityClass, 1, static_cast<int32>(info.Command), this));
//		}
//	}
//
//	BindAbilitySystemToInputComponent();
//}
//
//void ATestCharacter::InitializeAttributes(UAbilitySystemComponent* pASC, const TSubclassOf<UGameplayEffect>& Effect)
//{
//	ENSURE(pASC);
//	ENSURE(Effect);
//
//	FGameplayEffectContextHandle EffectContext = pASC->MakeEffectContext();
//	EffectContext.AddSourceObject(this);
//
//	FGameplayEffectSpecHandle NewHandle = pASC->MakeOutgoingSpec(Effect, 1, EffectContext);
//	ENSURE(NewHandle.IsValid());
//
//	FActiveGameplayEffectHandle ActiveGEHandle = pASC->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
//}