// CC Jacob Terry 2023


#include "Player/PCPlayerController.h"
#include "Player/PCPlayerState.h"
#include "AbilitySystemComponent.h"

void APCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APCPlayerState* PS = GetPlayerState<APCPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

//TODO add hud stuff
