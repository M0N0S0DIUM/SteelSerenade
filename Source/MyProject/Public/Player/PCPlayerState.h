// CC Jacob Terry 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "GameplayEffectTypes.h"
#include "PCPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	APCPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UCharacterAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|Attributes")
	float GetResonance() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|Attributes")
	float GetMaxResonance() const;

	UFUNCTION(BlueprintCallable, Category = "Game|PCPlayerState|Attributes")
	int32 GetCharacterLevel() const;


protected:

	UPROPERTY()
	class UCharacterAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY() 
	class UCharacterAttributeSetBase* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle ResonanceChangedDelegateHandle;
	FDelegateHandle MaxResonanceChangedDelegateHandle;
	FDelegateHandle CharacterLevelChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ResonanceChanged(const FOnAttributeChangeData& Data);
	virtual void MaxResonanceChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

};
