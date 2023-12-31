


#include "Character/PlayerCharacterBase.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/Abilities/AttributeSets/CharacterAttributeSetBase.h"
#include "Character/Abilities/CharacterGameplayAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));

}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UCharacterGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void APlayerCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid()) 
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}

}
void APlayerCharacterBase::AddStartupEffects()
{

	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied) {
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}


void APlayerCharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid()) {
		AttributeSetBase->SetHealth(Health);
	}
}

void APlayerCharacterBase::SetResonance(float Resonance)
{
	if (AttributeSetBase.IsValid()) {
		AttributeSetBase->SetResonance(Resonance);
	}
}


UAbilitySystemComponent* APlayerCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

bool APlayerCharacterBase::IsAlive() const
{
	return GetHealth() >0.0f;
}

int32 APlayerCharacterBase::GetAbilityLevel(PlayerAbilityID AbilityID) const
{
	return 1;
}

void APlayerCharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven){
		return;

	}
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities()) 
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++) {
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = false;

}

void APlayerCharacterBase::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid()) 
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		FinishDying();
	}
}

void APlayerCharacterBase::FinishDying()
{
	Destroy();
}

float APlayerCharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase.IsValid()) {
		return AttributeSetBase->GetLevel();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid()) {
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxHealth() const
{
	if (AttributeSetBase.IsValid()) {
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetResonance() const
{
	if (AttributeSetBase.IsValid()) {
		return AttributeSetBase->GetResonance();
	}

	return 0.0f;
}

float APlayerCharacterBase::GetMaxResonance() const
{
	if (AttributeSetBase.IsValid()) {
		return AttributeSetBase->GetHealth();
	}

	return 0.0f;
}


