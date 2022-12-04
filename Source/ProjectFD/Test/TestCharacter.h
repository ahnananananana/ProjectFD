#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;



DECLARE_MULTICAST_DELEGATE(FTestDelegate);

class FTestStruct1 : public TSharedFromThis<FTestStruct1>
{
public:
	FTestDelegate del1;
	

	void Test()
	{
		UE_LOG(LogTemp, Log, TEXT("asd"));
	}
};

void StaticTest();
class USphereComponent;
UCLASS()
class PROJECTFD_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

//	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
//	TSubclassOf<UGameplayEffect> DefaultAttributes;
//
//	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
//	TSubclassOf<UGameplayEffect> TestEffect;
//
//	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
//	TArray<FAbilityBindInfo> DefaultAbilities;
//
//	FTestDelegate del1;
//	TSharedPtr<FTestStruct1> a;
//
//public:
//	// Sets default values for this character's properties
//	ATestCharacter();
//
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	USphereComponent* s1;
	USphereComponent* s2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TObjectPtr<USphereComponent> s3;
	TObjectPtr<USphereComponent> s4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Classes)
	TWeakObjectPtr<USphereComponent> s5;
	TWeakObjectPtr<USphereComponent> s6;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AGameStateBase> GameStateClass1;
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AGameStateBase> GameStateClass2;

	void BeginPlay() override;
//	void PossessedBy(AController* NewController) override;
//	void OnRep_PlayerState() override;
//
public:	
//	// Called every frame
	void Tick(float DeltaTime) override;
//	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//private:
//	void InitializeAbilitySystemComponent();
//	void InitializeAttributes(UAbilitySystemComponent* pASC, const TSubclassOf<UGameplayEffect>& pEffect);
//	void BindAbilitySystemToInputComponent();
//
//	void Test();
//	volatile int aa;
//	UFUNCTION(meta = (AllowPrivateAccess = "true"))
//	void Test2();
};
