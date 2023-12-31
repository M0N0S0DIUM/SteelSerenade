
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyProject/MyProject.h"
#include "CharacterGameplayAbility.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT_API UCharacterGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCharacterGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	PlayerAbilityID AbilityInputID = PlayerAbilityID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	PlayerAbilityID AbilityID = PlayerAbilityID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
