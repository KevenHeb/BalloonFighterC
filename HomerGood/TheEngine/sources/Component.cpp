#include "Component.h"
#include "Entity.h"
#include "Engine.h"

homer::Component::Component(Entity* parent)
{
    m_Entity = parent;
}

homer::Entity* homer::Component::GetParentEntity()
{
    return m_Entity;
}

void homer::Component::Exit()
{
    Engine::Get().Exit();
}

//Codes utilisées pour permettre au Component d'accéder au service de l'engin rapidement.
homer::IInput& homer::Component::Input() const
{
    return Engine::Get().Input();
}

homer::ILogger& homer::Component::Logger() const
{
    return Engine::Get().Logger();
}

homer::IGraphics& homer::Component::Graphics() const
{
    return Engine::Get().Graphics();
}

homer::IAudio& homer::Component::Audio() const
{
    return Engine::Get().Audio();
}

homer::IWorld& homer::Component::WorldService() const
{
    return Engine::Get().WorldService();
}

homer::ICollision& homer::Component::Collisions() const
{
    return Engine::Get().Collisions();
}
