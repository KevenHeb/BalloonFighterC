#include "Entity.h"
#include "Engine.h"
#include "Atlas.h"

homer::Entity::Entity(const std::string& name)
{
    m_Name = name;
    /*m_Position = RectF{
        0,0,0,0
    };*/
}

homer::Entity::Entity(const std::string& name, RectF dst)
{
    m_Name = name;
    m_Position = dst;
}

//Au début du jeu, appele la methode start de chaque component de l'entité
void homer::Entity::Start()
{
    for (auto cmp : m_AllComponents)
    {
        cmp->Start();
    }
}

//A chaque frame, appele la methode de tout les components qui hérite de IUpdatable
void homer::Entity::Update(float dt)
{
    for (auto cmp : m_ComponentToUpdate)
    {
        cmp->Update(dt);
    }
}

//A chaque frame, appele la methode de tout les components qui hérite de IDrawable
void homer::Entity::Draw()
{
    for (auto cmp : m_ComponentToDraw)
    {
        cmp->Draw();
    }
}

//A la fin du programme, détruit chaque components de chaque entité et vide les listes
void homer::Entity::Destroy()
{
    for (auto cmp : m_AllComponents)
    {
        cmp->Destroy();
        delete cmp;
    }    
    m_AllComponents.clear();
    m_ComponentByType.clear();
    m_ComponentToDraw.clear();
    m_ComponentToUpdate.clear();
}

void homer::Entity::SetPosition(RectF dst)
{
    m_Position = dst;
}

void homer::Entity::SetPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}

void homer::Entity::SetSize(float w, float h)
{
    m_Position.w = w;
    m_Position.h = h;
}

void homer::Entity::Move(int x, int y)
{
    m_Position.x += x;
    m_Position.y += y;
}

std::string& homer::Entity::GetName()
{
    return m_Name;
}

homer::RectF homer::Entity::GetPosition()
{
    return m_Position;
}

void homer::Entity::GetPosition(float* x, float* y)
{
    *x = m_Position.x;
    *y = m_Position.y;
}

void homer::Entity::GetSize(float* w, float* h)
{
    *w = m_Position.w;
    *h = m_Position.h;
}


float homer::Entity::GetX()
{
    return m_Position.x;
}

float homer::Entity::GetY()
{
    return m_Position.y;
}

float homer::Entity::GetW()
{
    return m_Position.w;
}

float homer::Entity::GetH()
{
    return m_Position.h;
}

