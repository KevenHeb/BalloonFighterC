#include "EnemyController.h"
#include "Engine.h"
#include "Entity.h"
#include "PumpState.h"
#include "EnemyFlyState.h"
#include "FallState.h"

homer::EnemyController::EnemyController(Entity* parent) : Character(parent)
{
	//m_DeathSound = Audio().LoadSound("Assets/enemy_dead.wav");
}

homer::EnemyController::~EnemyController()
{
	std::map<std::string, IEnemyState*>::iterator it;
	for (it = m_States.begin(); it != m_States.end(); it++)
	{
		delete it->second;
	}
	m_States.clear();
	OnDestroy.RemoveAllListeners();
}

void homer::EnemyController::Start()
{
	m_States.emplace("Pump", new PumpState());
	m_States.emplace("Fly", new EnemyFlyState());
	m_States.emplace("Fall", new FallState());

	m_DeathSound = Audio().LoadSound("Assets/enemy_dead.wav");
	m_IndexMap.emplace("Water", std::vector<int>{53, 37});
	m_IndexMap.emplace("Floor", std::vector<int>{5, 6, 7, 8});
	m_Animation = m_Entity->GetComponent<Animation>();
	m_Atlas = m_Entity->GetComponent<Atlas>();

	RectF feetPos{
		m_Entity->GetX() + (m_Entity->GetW() * 0.1f),
		m_Entity->GetY() + m_Entity->GetH() * 0.75f,
		m_Entity->GetW() - (m_Entity->GetW() * 0.2f),
		m_Entity->GetH() * 0.25f
	};

	RectF balloonPos{
		m_Entity->GetX() + (m_Entity->GetW() * 0.15f),
		m_Entity->GetY() + m_Entity->GetH() * 0.5f,
		m_Entity->GetW() - (m_Entity->GetW() * 0.2f),
		m_Entity->GetH() * 0.25f
	};

	m_FeetCollider = WorldService().Create(m_Entity->GetName() + "FeetCollider");
	m_BalloonCollider = WorldService().Create(m_Entity->GetName() + "BalloonCollider");

	m_FeetCollider->SetPosition(feetPos);
	m_BalloonCollider->SetPosition(balloonPos);

	Collisions().AddToLayer("Enemy", m_Entity);
	Collisions().AddToLayer("EnemyFeet", m_FeetCollider);
	Collisions().AddToLayer("EnemyBalloon", m_BalloonCollider);
	
	ChangeState("Pump");

	m_Lowest = m_Entity->GetY() + 50;
	m_Highest = m_Entity->GetY() - 50;
}

void homer::EnemyController::Update(float dt)
{
	int index = 0;
	if (m_Tilemap == nullptr)
	{
		m_Tilemap = WorldService().Find("TileMap")->GetComponent<Tilemap>();
	}

	m_CurrentState->Execute(this);
	if (m_CurrentState == m_States["Fly"])
	{
		if (m_Entity->GetY() > m_Lowest)
		{
			m_DirectionY = -1;
		}
		else if (m_Entity->GetY() < m_Highest)
		{
			m_DirectionY = 1;
		}
		if (m_Entity->GetX() + m_Entity->GetW() > 800)
		{
			m_DirectionX = -1;
			m_Atlas->SetFlip(false, false);
		}
		else if (m_Entity->GetX() < 0)
		{
			m_DirectionX = 1;
			m_Atlas->SetFlip(true, false);
		}
		m_Entity->Move(m_DirectionX, m_DirectionY);

		m_FeetCollider->SetPosition(m_Entity->GetX() + (m_Entity->GetW() * 0.1f),
			m_Entity->GetY() + m_Entity->GetH() * 0.75f);
		m_BalloonCollider->SetPosition(m_Entity->GetX() + (m_Entity->GetW() * 0.15f),
			m_Entity->GetY() + m_Entity->GetH() * 0.25f);

		if (m_Tilemap->IsColliding("Foreground", m_FeetCollider->GetX(), m_FeetCollider->GetY(), m_FeetCollider->GetW(), m_FeetCollider->GetH(), &index))
		{
			for (auto tileIndex : m_IndexMap["Floor"])
			{
				if (index == tileIndex)
				{
					m_DirectionY = -1;
					break;
				}
			}
		}
		else if (m_Tilemap->IsColliding("Foreground", m_BalloonCollider->GetX(), m_BalloonCollider->GetY(), m_BalloonCollider->GetW(), m_BalloonCollider->GetH(), &index))
		{
			for (auto tileIndex : m_IndexMap["Floor"])
			{
				if (index == tileIndex)
				{
					m_DirectionY = 1;
					break;
				}
			}
		}
	}	
	

	if (m_CurrentState == m_States["Fall"])
	{	
		if (m_Tilemap->IsColliding("Foreground", m_Entity->GetX(), m_Entity->GetY(), m_Entity->GetW(), m_Entity->GetH(), &index))
		{
			for (auto tileIndex : m_IndexMap["Water"])
			{
				if (index == tileIndex)
				{
					Audio().PlaySFX(m_DeathSound);
					WorldService().Remove(m_Entity->GetName());
					OnDestroy.Invoke(m_Entity->GetPosition());
					WorldService().EnemyDefeated();
				}
			}
		}
	}
}

void homer::EnemyController::Hit()
{
	ChangeState("Fall");
	if (m_BalloonCollider != nullptr && m_FeetCollider != nullptr)
	{
		//Mes les colliders hors ecran pour eviter un bug qui existe seulement dans la version Release.
		m_FeetCollider->SetPosition(1000, 1000);

		WorldService().AddScore(m_Points);
		WorldService().Remove(m_BalloonCollider->GetName());
		WorldService().Remove(m_FeetCollider->GetName());
		m_FeetCollider = nullptr;
		m_BalloonCollider = nullptr;
	}
}

void homer::EnemyController::ChangeState(const std::string& state)
{
	if (m_States.count(state) > 0 && m_CurrentState != m_States[state])
	{
		m_CurrentState = m_States[state];
	}
	m_CurrentState->Enter(this);
}

homer::Animation* homer::EnemyController::GetAnimation()
{
	return m_Animation;
}
