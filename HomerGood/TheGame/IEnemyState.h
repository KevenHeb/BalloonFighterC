#pragma once
namespace homer
{
	class EnemyController;

	//States pour les ennemies
	class IEnemyState
	{
	public:
		//Lorsque l'ennemie entre dans cette state, elle appele cette fonction
		//<param> theEnemy : component représentant l'ennemie.
		virtual void Enter(EnemyController* theEnemy) = 0;

		//Cette fonction est exécuter à chaque frame
		//<param> theEnemy : component représentant l'ennemie.
		virtual void Execute(EnemyController* theEnemy) = 0;
	};
}