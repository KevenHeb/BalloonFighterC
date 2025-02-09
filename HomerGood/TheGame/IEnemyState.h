#pragma once
namespace homer
{
	class EnemyController;

	//States pour les ennemies
	class IEnemyState
	{
	public:
		//Lorsque l'ennemie entre dans cette state, elle appele cette fonction
		//<param> theEnemy : component repr�sentant l'ennemie.
		virtual void Enter(EnemyController* theEnemy) = 0;

		//Cette fonction est ex�cuter � chaque frame
		//<param> theEnemy : component repr�sentant l'ennemie.
		virtual void Execute(EnemyController* theEnemy) = 0;
	};
}