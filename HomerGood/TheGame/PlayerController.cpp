#include "PlayerController.h"
#include "Engine.h"
#include "Entity.h"
#include "GroundedState.h"
#include "FlyingState.h"
#include "EnemyController.h"

float const JUMP_FORCE = 5.0f;

homer::PlayerController::PlayerController(Entity* parent) : Character(parent)
{
	
}

homer::PlayerController::~PlayerController()
{
	std::map<std::string, IPlayerState*>::iterator it;
	for (it = m_States.begin(); it != m_States.end(); it++)
	{
		delete it->second;
	}
	m_States.clear();
}

void homer::PlayerController::Start()
{
	m_FlySFX = Audio().LoadSound("Assets/fly.wav");
	m_PopSFX = Audio().LoadSound("Assets/balloon_pop.wav");
	m_Dead = false;
	m_Atlas = m_Entity->AddComponent<Atlas>();
	m_Atlas->SetId("Assets/balloon_fighter_sheet.png");
	m_Animation = m_Entity->AddComponent<Animation>();

	m_States.emplace("Grounded", new GroundedState());
	m_States.emplace("Fly", new FlyingState());

	m_Atlas->AddFrame("Default", 0, 0, 16, 32);
	m_Atlas->SetFrame("Default");

	m_Animation->InitAnimation(4, 16, 32);

	m_Animation->AddClip("IdleTwo", 0, 0, 4, 0.15f);
	m_Animation->AddClip("IdleOne", 3, 0, 4, 0.15f);

	m_Animation->AddClip("WalkTwo", 1, 0, 4, 0.15f);
	m_Animation->AddClip("WalkOne", 4, 0, 4, 0.15f);

	m_Animation->AddClip("JumpTwo", 2, 0, 4, 0.15f);
	m_Animation->AddClip("JumpOne", 5, 0, 4, 0.15f);

	m_Animation->AddClip("AirIdleTwo", 2, 3, 1, 200.0f);
	m_Animation->AddClip("AirIdleOne", 5, 3, 1, 200.0f);

	m_Animation->AddClip("Death", 6, 0, 4, 0.5f);
	m_Animation->AddClip("Hit", 7, 0, 1, 0.5f);

	m_Animation->Play("IdleTwo", true);

	m_IndexMap.emplace("Floor", std::vector<int>{5, 6, 7, 8});
	m_IndexMap.emplace("Water", std::vector<int>{53, 37});
	ChangeState("Fly");

	m_FeetCollider = WorldService().Create("PlayerFeet");
	m_BalloonCollider = WorldService().Create("PlayerBalloon");

	Collisions().AddToLayer("PlayerFeet", m_FeetCollider);
	Collisions().AddToLayer("Player", m_Entity);
	Collisions().AddToLayer("PlayerBalloon", m_BalloonCollider);

	RectF feetPos{
		m_Entity->GetX() + (m_Entity->GetW() * 0.1f),
		m_Entity->GetY() + m_Entity->GetH(),
		m_Entity->GetW() - (m_Entity->GetW() * 0.2f),
		0.5f
	};	

	RectF balloonPos{
		m_Entity->GetX() + (m_Entity->GetW() * 0.15f),
		m_Entity->GetY() + m_Entity->GetH() * 0.25f,
		m_Entity->GetW() - (m_Entity->GetW() * 0.3f),
		m_Entity->GetH() * 0.5f /2
	};
	m_FeetCollider->SetPosition(feetPos);
	m_BalloonCollider->SetPosition(balloonPos);
}

void homer::PlayerController::Update(float dt)
{
	if (m_Tilemap == nullptr)
	{
		Entity* tilemap = WorldService().Find("TileMap");
		m_Tilemap = tilemap->GetComponent<Tilemap>();
	}

	if (m_Invincible)
	{
		m_InvTimer -= dt;
		if (m_InvTimer <= 0)
		{
			m_CurrentState->Idle(this);
			m_Invincible = false;
		}
	}

	if (!m_Dead)
	{
		//int index = 0;
		float x = m_Entity->GetX();
		float y = m_Entity->GetY();

		IInput& input = Input();

		float movement = 0;

		if (input.IsKeyDown(EKey::EKEY_SPACE))
		{
			if (!m_SpaceDown)
			{
				Jump();
				m_JumpVelocity = JUMP_FORCE;
				m_SpaceDown = true;
			}
		}
		else
		{
			m_SpaceDown = false;
		}

		if (input.IsKeyDown(EKey::EKEY_A))
		{
			movement = -m_Speed * dt;
			m_CurrentState->Move(this);
			//m_Entity->Move(-m_Speed, 0);
			m_Atlas->SetFlip(false, false);
		}
		else if (input.IsKeyDown(EKey::EKEY_D))
		{
			movement = m_Speed * dt;
			m_CurrentState->Move(this);
			//m_Entity->Move(m_Speed, 0);
			m_Atlas->SetFlip(true, false);
		}
		else
		{
			m_CurrentState->Idle(this);
		}

		m_Entity->Move(static_cast<int>(movement), -static_cast<int>(m_JumpVelocity));
		if (m_Entity->GetX() < 0 || m_Entity->GetX() + m_Entity->GetW() > 800)
		{
			m_Entity->SetPosition(x, m_Entity->GetY());
		}
		if (m_Entity->GetY() < 0)
		{
			m_Entity->SetPosition(m_Entity->GetX(), y);
		}

		m_FeetCollider->SetPosition(m_Entity->GetX() + (m_Entity->GetW() * 0.1f), m_Entity->GetY() + m_Entity->GetH());
		m_BalloonCollider->SetPosition(m_Entity->GetX() + (m_Entity->GetW() * 0.15f), m_Entity->GetY() + (m_Entity->GetH() * 0.25f));
		ManageCollisions(x, y);
	}
	else
	{
		if (!m_Animation->GetIsPlaying())
		{
			WorldService().ResetScore();
			WorldService().Load("Title");
		}
	}
}

void homer::PlayerController::Jump()
{
	Audio().PlaySFX(m_FlySFX);
	ChangeState("Fly");
	if (m_Balloons > 1)
	{
		//m_Atlas->SetId("Assets/player_jump_two.png");
		m_Animation->Play("JumpTwo", false);
	}
	else
	{
		//m_Atlas->SetId("Assets/player_jump_one.png");
		m_Animation->Play("JumpOne", false);
	}
	//m_Animation->Play("Jump", false);
	//m_CurrentState->Jump(this);
}

void homer::PlayerController::Hit()
{
	m_JumpVelocity = -2;
	if (!m_Invincible && m_Balloons > 0)
	{
		Audio().PlaySFX(m_PopSFX);
		m_Balloons -= 1;
		if (m_Balloons == 0)
		{
			m_Dead = true;
			m_Animation->Play("Death", false);
		}
		else
		{
			m_Animation->Play("Hit", false);
			m_CurrentState->Move(this);
			m_Invincible = true;
			m_InvTimer = 3.0f;
		}
	}
}

void homer::PlayerController::ManageCollisions(float x, float y)
{
	int index = 0;
	Entity* a;
	if (Collisions().CollideWithLayer(m_BalloonCollider, "EnemyFeet", &a))
	{
		Hit();
	}
	else if (Collisions().CollideWithLayer(m_FeetCollider, "Enemy", &a))
	{
		Entity* b;
		if (Collisions().CollideWithLayer(m_FeetCollider, "EnemyBalloon", &b))
		{
			a->GetComponent<EnemyController>()->Hit();
			Audio().PlaySFX(m_PopSFX);
		}
	}

	if (m_Tilemap->IsColliding("Foreground", m_BalloonCollider->GetX(), m_BalloonCollider->GetY(), m_BalloonCollider->GetW(), m_BalloonCollider->GetH(), &index))
	{
		for (auto tileIndex : m_IndexMap["Floor"])
		{
			if (index == tileIndex)
			{
				m_JumpVelocity = -static_cast<float>(WorldService().GetGravity());
				m_Entity->SetPosition(m_Entity->GetX(), y);
				break;
			}
		}
	}

	if (m_Tilemap->IsColliding("Foreground", m_FeetCollider->GetX(), m_FeetCollider->GetY(), m_FeetCollider->GetW(), m_FeetCollider->GetH(), &index))
	{
		for (auto tileIndex : m_IndexMap["Floor"])
		{
			if (index == tileIndex)
			{
				m_JumpVelocity = -static_cast<float>(WorldService().GetGravity());
				m_Entity->SetPosition(m_Entity->GetX(), y);
				ChangeState("Grounded");
				break;
			}
		}
	}

	else if (m_Tilemap->IsColliding("Foreground", m_Entity->GetX(), m_Entity->GetY(), m_Entity->GetW(), m_Entity->GetH(), &index))
	{
		for (auto tileIndex : m_IndexMap["Floor"])
		{
			if (index == tileIndex)
			{
				m_Entity->SetPosition(x, m_Entity->GetY());
			}
		}
		for (auto tileIndex : m_IndexMap["Water"])
		{
			if (index == tileIndex)
			{
				m_Dead = true;
				m_Animation->Play("Death", false);
			}
		}
	}

	else
	{
		ChangeState("Fly");
		m_JumpVelocity -= 0.1f;
		if (m_JumpVelocity < -3.0f)
		{
			m_JumpVelocity = -static_cast<float>(WorldService().GetGravity());
		}
	}
}

int homer::PlayerController::GetBalloons()
{
	return m_Balloons;
}


homer::Animation* homer::PlayerController::GetAnimation()
{
	return m_Animation;
}

void homer::PlayerController::ChangeState(const std::string& state)
{
	if (m_States.count(state) > 0 && m_CurrentState != m_States[state])
	{
		if (m_CurrentState != nullptr)
		{
			m_CurrentState->Exit(this);
		}
		m_CurrentState = m_States[state];
		m_CurrentState->Enter(this);
	}
}
