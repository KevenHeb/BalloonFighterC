#include "PlayerController.h"
#include "Engine.h"
#include "Entity.h"
#include "Atlas.h"

float const JUMP_FORCE = 5.0f;

homer::PlayerController::PlayerController(Entity* parent) : Component(parent)
{

}

void homer::PlayerController::Update(float dt)
{
	IInput& input = Input();

	if (input.IsKeyDown(EKey::EKEY_SPACE))
	{
		Jump();
	}

	if (input.IsKeyDown(EKey::EKEY_S))
	{
		m_Entity->Move(0, m_Speed);
		//this->m_Entity->GetComponent<Animation>()->SetRow(0);
	}
	if (input.IsKeyDown(EKey::EKEY_A))
	{
		m_Entity->Move(-m_Speed, 0); 
		m_Entity->GetComponent<Atlas>()->SetFlip(false, false);
		//this->m_Entity->GetComponent<Animation>()->SetRow(2);
	}
	else if (input.IsKeyDown(EKey::EKEY_D))
	{
		m_Entity->Move(m_Speed, 0);
		m_Entity->GetComponent<Atlas>()->SetFlip(true, false);
		//this->m_Entity->GetComponent<Animation>()->SetRow(1);
	}

	if (m_JumpVelocity > 0)
	{
		if (m_JumpVelocity >= 3.0f)
		{
			m_Entity->Move(0, -3);
		}
		else
		{
			m_Entity->Move(0, -static_cast<int>(m_JumpVelocity));
		}
		//Temp
		m_JumpVelocity -= WorldService().GetGravity() * dt;
	}
	else if (m_JumpVelocity < 0)
	{
		m_JumpVelocity = 0;
	}
}

void homer::PlayerController::Jump()
{
	m_JumpVelocity = JUMP_FORCE;
}

void homer::PlayerController::Hit()
{
	m_Balloons -= 1;
	if (m_Balloons == 0)
	{
		//Play Death
	}
}
