// CC Jacob Terry 2023


#include "Player/PCPlayerState.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"

APCPlayerState::APCPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UCharacterAttributeSetBase>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* APCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAttributeSetBase* APCPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool APCPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void APCPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO HUD
}

float APCPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float APCPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float APCPlayerState::GetResonance() const
{
	return AttributeSetBase->GetResonance();
}

float APCPlayerState::GetMaxResonance() const
{
	return AttributeSetBase->GetMaxResonance();
}

int32 APCPlayerState::GetCharacterLevel() const
{
	return AttributeSetBase->GetLevel();
}

void APCPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent) 
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &APCPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &APCPlayerState::MaxHealthChanged);
		ResonanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetResonanceAttribute()).AddUObject(this, &APCPlayerState::ResonanceChanged);
		MaxResonanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxResonanceAttribute()).AddUObject(this, &APCPlayerState::MaxResonanceChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetLevelAttribute()).AddUObject(this, &APCPlayerState::CharacterLevelChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &APCPlayerState::StunTagChanged);
	}

}

void APCPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Health Changed."));
}

void APCPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Health Changed."));
}

void APCPlayerState::ResonanceChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Resonance Changed."));
}

void APCPlayerState::MaxResonanceChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Max Resonance Changed."));
}

void APCPlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Level Changed."));
}

void APCPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
