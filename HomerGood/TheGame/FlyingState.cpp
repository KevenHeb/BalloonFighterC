#include "FlyingState.h"
#include "PlayerController.h"
#include "Entity.h"

void homer::FlyingState::Enter(PlayerController* thePlayer)
{
	Idle(thePlayer);
}


void homer::FlyingState::Move(PlayerController* thePlayer)
{
	m_IsIdle = false;
}

void homer::FlyingState::Idle(PlayerController* thePlayer)
{
	if (!m_IsIdle)
	{
		if (thePlayer->GetBalloons() > 1)
		{
			thePlayer->GetAnimation()->Play("AirIdleTwo", false);
		}
		else
		{
			thePlayer->GetAnimation()->Play("AirIdleOne", false);
		}
		m_IsIdle = true;
	}
}

void homer::FlyingState::Exit(PlayerController* thePlayer)
{
	m_IsIdle = false;
}
