#include "FallState.h"
#include "EnemyController.h"
#include "Entity.h"
#include "Engine.h"

void homer::FallState::Enter(EnemyController* theEnemy)
{
	theEnemy->GetAnimation()->Play("Fall", true);
}

void homer::FallState::Execute(EnemyController* theEnemy)
{
	theEnemy->GetParentEntity()->Move(0, Engine::Get().WorldService().GetGravity());
}
