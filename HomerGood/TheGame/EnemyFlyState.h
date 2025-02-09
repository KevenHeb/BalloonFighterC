#pragma once
#include "IEnemyState.h"

namespace homer
{
	//State pour lorsque l'ennemie vole. 
	class EnemyFlyState : public IEnemyState
	{
	public:
		virtual void Enter(EnemyController* theEnemy) override;
		virtual void Execute(EnemyController* theEnemy) override;
	};
}