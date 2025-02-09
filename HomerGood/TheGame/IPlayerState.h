#pragma once

namespace homer
{
	class PlayerController;

	//State pour le joueur.
	class IPlayerState
	{
	public:
		//Lorsque le joueur entre dans cette state, elle appele cette fonction
		//<param> thePlayer : component représentant le joueur.
		virtual void Enter(PlayerController* thePlayer) = 0;

		//Si le joueur bouge, appele cette fonction
		//<param> thePlayer : component représentant le joueur.
		virtual void Move(PlayerController* thePlayer) = 0;

		//Si le joueur ne bouge pas, appele cette fonction
		//<param> thePlayer : component représentant le joueur.
		virtual void Idle(PlayerController* thePlayer) = 0;

		//Quand le joueur sort de cette state, appele cette fonction.
		//<param> thePlayer : component représentant le joueur.
		virtual void Exit(PlayerController* thePlayer) = 0;
	};
}