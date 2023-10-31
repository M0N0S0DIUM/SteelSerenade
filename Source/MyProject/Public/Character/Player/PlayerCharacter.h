// CC Jacob Terry 2023

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacterBase.h"
#include "Player/PCPlayerState.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public APlayerCharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	//class USpringArmComponent* GetCameraBoom();

	//class UCameraComponent* GetFollowCamera();

	//UFUNCTION(BlueprintCallable, Category = "Player|Camera")
	float GetStartingCameraBoomArmLength();

	//UFUNCTION(BlueprintCallable, Category = "Player|Camera")
	FVector GetStartingCameraBoomLocation();

protected:

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Camera")
	float BaseTurnRate = 45.0f;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player|Camera")
	float BaseLookUpRate = 45.0f;

	//UPROPERTY(BlueprintReadOnly, Category = "Player|Camera")
	float StartingCameraBoomArmLength;

	//UPROPERTY(BlueprintReadOnly, Category = "Player|Camera")
	FVector StartingCameraBoomLocation;

	//UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Player|Camera")
	class USpringArmComponent* CameraBoom;

	//UPROPERTY(BlueprintReadOnly, Category = "Player|Camera")
	class UCameraComponent* FollowCamera;

	//bool ASCInputBound = false;

	FGameplayTag DeadTag;

	virtual void BeginPlay() override;

	//void LookUp(float Value);

	//void LookUpRate(float Value);

	//void Turn(float Value);

	//void TurnRate(float Value);

	//void MoveForward(float Value);

	//void MoveRight(float Value);

	virtual void OnRep_PlayerState() override;

	void InitStartingValues(APCPlayerState* PS);

	//void BindASCInput();

};
