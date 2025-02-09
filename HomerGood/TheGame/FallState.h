#pragma once
#include "IEnemyState.h"

namespace homer
{
	//State pour lorsque l'ennemie tombe.
	class FallState : public IEnemyState
	{
	public:
		virtual void Enter(EnemyController* theEnemy) override;
		virtual void Execute(EnemyController* theEnemy) override;
	};
}