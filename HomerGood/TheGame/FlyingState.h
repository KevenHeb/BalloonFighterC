#pragma once
#pragma once
#include "IPlayerState.h"

namespace homer
{
	//State pour quand le joueur vole.
	class FlyingState : public IPlayerState
	{
	public:
		virtual void Enter(PlayerController* thePlayer) override;
		virtual void Move(PlayerController* thePlayer) override;
		virtual void Idle(PlayerController* thePlayer) override;
		virtual void Exit(PlayerController* thePlayer) override;

	private:
		bool m_IsIdle = false;
	};
}