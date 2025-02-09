#include "BubbleComponent.h"
#include "Entity.h"
#include "Engine.h"
#include "Atlas.h"

homer::BubbleComponent::BubbleComponent(Entity* parent) : Component(parent)
{
	m_PopSFX = Audio().LoadMusic("Assets/balloon_pop.wav");
}

void homer::BubbleComponent::Update(float dt)
{
	m_Entity->Move(0, -static_cast<int>(100 * dt));
	Entity* other;
	if (Collisions().CollideWithLayer(m_Entity, "Player", &other))
	{
		Audio().PlaySFX(m_PopSFX);
		Hit();
	}
	if (m_Entity->GetY() < 0)
	{
		WorldService().Remove(m_Entity->GetName());
	}
}

void homer::BubbleComponent::Hit()
{
	WorldService().AddScore(points);
	WorldService().Remove(m_Entity->GetName());
}
