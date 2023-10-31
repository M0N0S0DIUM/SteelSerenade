// CC Jacob Terry 2023


#include "Character/Player/PlayerCharacter.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Ai/PlayerAIController.h"
#include "Player/PCPlayerState.h"
#include "Character/Player/PlayerCharacter.h"
#include "Player/PCPlayerController.h"
#include "Character/Abilities/CharacterAbilitySystemComponent.h"
//#include "Kismet/KismetMathLibrary.h"


APlayerCharacter::APlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->bUsePawnControlRotation = true;
	//CameraBoom->SetRelativeLocation(FVector(0, 0, 70));

	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom);
	//FollowCamera->FieldOfView = 80.0f;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	AIControllerClass = APlayerAIController::StaticClass();

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

/*
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnRate);

	BindASCInput();
}
*/
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APCPlayerState* PS = GetPlayerState<APCPlayerState>();
	if (PS)
	{
		InitStartingValues(PS);

		AddStartupEffects();
		AddCharacterAbilities();

	}

}
/*
USpringArmComponent* APlayerCharacter::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* APlayerCharacter::GetFollowCamera()
{
	return FollowCamera;
}

float APlayerCharacter::GetStartingCameraBoomArmLength()
{
	return StartingCameraBoomArmLength;
}

FVector APlayerCharacter::GetStartingCameraBoomLocation()
{
	return StartingCameraBoomLocation;
}
*/
void APlayerCharacter::BeginPlay()
{

	Super::BeginPlay();

	//StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
	//StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();

}
/*
void APlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}

void APlayerCharacter::LookUpRate(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->DeltaTimeSeconds);
	}
}

void APlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}

void APlayerCharacter::TurnRate(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value * BaseTurnRate * GetWorld()->DeltaTimeSeconds);
	}
}

void APlayerCharacter::MoveForward(float value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (IsAlive())
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), value);
	}
}
*/
void APlayerCharacter::OnRep_PlayerState()
{

	Super::OnRep_PlayerState();
	APCPlayerState* PS = GetPlayerState<APCPlayerState>();
	if (PS)
	{
		InitStartingValues(PS);
		//BindASCInput();
	}

}

void APlayerCharacter::InitStartingValues(APCPlayerState* PS)
{

	AbilitySystemComponent = Cast<UCharacterAbilitySystemComponent>(PS->GetAbilitySystemComponent());

	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AttributeSetBase = PS->GetAttributeSetBase();

	AbilitySystemComponent->SetTagMapCount(DeadTag, 0);

	InitializeAttributes();

	SetHealth(GetMaxHealth());
	SetResonance(GetMaxResonance());
}
/*
void APlayerCharacter::BindASCInput()
{

	if (!ASCInputBound && AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("PlayerAbilityID"), static_cast<int32>(PlayerAbilityID::Cancel)));

		ASCInputBound = true;
	}

}
*/
