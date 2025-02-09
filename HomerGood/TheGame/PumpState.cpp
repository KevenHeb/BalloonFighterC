#include "PumpState.h"
#include "EnemyController.h"

void homer::PumpState::Enter(EnemyController* theEnemy)
{
	theEnemy->GetAnimation()->Play("Pump", false);
}

void homer::PumpState::Execute(EnemyController* theEnemy)
{
	if (!theEnemy->GetAnimation()->GetIsPlaying())
	{
		theEnemy->ChangeState("Fly");
	}
}
