#include "GroundedState.h"
#include "PlayerController.h"
#include "Entity.h"

void homer::GroundedState::Enter(PlayerController* thePlayer)
{
	Idle(thePlayer);
}

void homer::GroundedState::Move(PlayerController* thePlayer)
{
	m_IsIdle = false;
	if (thePlayer->GetAnimation()->GetCurrentClip() != "WalkTwo" &&
		thePlayer->GetAnimation()->GetCurrentClip() != "WalkOne")
	{
		if (thePlayer->GetBalloons() > 1)
		{
			thePlayer->GetAnimation()->Play("WalkTwo", true);
		}
		else
		{
			thePlayer->GetAnimation()->Play("WalkOne", true);
		}
	}
}

void homer::GroundedState::Idle(PlayerController* thePlayer)
{
	if (!m_IsIdle)
	{
		if (thePlayer->GetBalloons() > 1)
		{
			thePlayer->GetAnimation()->Play("IdleTwo", true);
		}
		else
		{
			thePlayer->GetAnimation()->Play("IdleOne", true);
		}
		m_IsIdle = true;
	}
}

void homer::GroundedState::Exit(PlayerController* thePlayer)
{
	m_IsIdle = false;
}
