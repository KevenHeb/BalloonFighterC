#include "EnemyFlyState.h"
#include "EnemyController.h"
#include "Entity.h"

void homer::EnemyFlyState::Enter(EnemyController* theEnemy)
{
	theEnemy->GetAnimation()->Play("Fly", true);
}

void homer::EnemyFlyState::Execute(EnemyController* theEnemy)
{
	
}
