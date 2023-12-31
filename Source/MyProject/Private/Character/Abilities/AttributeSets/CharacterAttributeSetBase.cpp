

#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Net/UnrealNetwork.h"

void UCharacterAttributeSetBase::OnRep_Level(const FGameplayAttributeData& OldLevel)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, Level, OldLevel);
}

void UCharacterAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, Health, OldHealth);
}
void UCharacterAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UCharacterAttributeSetBase::OnRep_Resonance(const FGameplayAttributeData& OldResonance)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, Resonance, OldResonance);
}
void UCharacterAttributeSetBase::OnRep_MaxResonance(const FGameplayAttributeData& OldMaxResonance)
{

	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSetBase, MaxResonance, OldMaxResonance);
}

void UCharacterAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, Resonance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCharacterAttributeSetBase, MaxResonance, COND_None, REPNOTIFY_Always);

}