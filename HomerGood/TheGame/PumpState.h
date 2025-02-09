#pragma once
#include "IEnemyState.h"

namespace homer
{
	//State pour l'ennemie au d�but du jeu lorsqu'il rempli sa balloon.
	class PumpState : public IEnemyState
	{
	public:
		virtual void Enter(EnemyController* theEnemy) override;
		virtual void Execute(EnemyController* theEnemy) override;
	};
}