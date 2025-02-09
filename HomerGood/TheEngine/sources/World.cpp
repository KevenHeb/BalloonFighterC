#include "World.h"
#include <Entity.h>
#include <Engine.h>
#include <IScene.h>

homer::World::~World()
{
    RemoveAllEntities();
}

void homer::World::StartEntities()
{
    if (m_EntityToStart.size() > 0)
    {
        std::vector<Entity*> _starting = m_EntityToStart;
        m_EntityToStart.clear();

        for (auto entity : _starting)
        {
            if (m_EntityMap.count(entity->GetName()) > 0)
            {
                Engine::Get().Logger().LogWarning("Not adding entity with same name");
                continue;
            }

            m_EntityInWorld.emplace_back(entity);
            m_EntityMap.emplace(entity->GetName(), entity);
        }

        for (auto entity : _starting)
        {
            entity->Start();
        }
        _starting.clear();
    }
}

//Appele la méthode Update de chaque entité dans le monde.
void homer::World::Update(float dt)
{
    StartEntities();
    for (auto entity : m_EntityInWorld)
    {
        entity->Update(dt);
    }
    if (m_CurrentScene == "Title")
    {
        if (Engine::Get().Input().IsKeyDown(EKey::EKEY_RETURN))
        {
            NextStage();
        }
    }
    UpdateLoadScene();
    DoDelete();
}

//Appele la méthode Draw de chaque entité dans le monde.
void homer::World::Draw()
{
    for (auto entity : m_EntityInWorld)
    {
        entity->Draw();
    }
}

//Ajoute une entité danss le monde.
homer::Entity* homer::World::Create(const std::string& name)
{
    for (auto entity : m_EntityToStart)
    {
        if (entity->GetName() == name)
        {
            return nullptr;
        }
    }
    Entity* _newEntity = new Entity(name);
    m_EntityToStart.emplace_back(_newEntity);
    return _newEntity;
}

//Détruit les entités qui doivent être détruite.
void homer::World::DoDelete()
{
    if (m_EntityToDelete.size() > 0)
    {
        std::vector<Entity*> _trash = m_EntityToDelete;
        m_EntityToDelete.clear();

        for (auto entity : _trash)
        {
            //entity->Destroy();
            for (auto it = m_EntityInWorld.begin(); it != m_EntityInWorld.end(); it++)
            {
                if (*it == entity)
                {
                    entity->Destroy();
                    Engine::Get().Collisions().Remove(entity);
                    m_EntityMap.erase(entity->GetName());
                    m_EntityInWorld.erase(it);
                    delete entity;
                    break;
                }
            }

            //m_EntityMap.erase(entity->GetName());
        }
        _trash.clear();
    }

}

void homer::World::RemoveAllEntities()
{
    for (auto entity : m_EntityInWorld)
    {
        Remove(entity->GetName());
    }
    DoDelete();
}

//Appele la méthode précédente. Le nom est utiliser pour trouver l'entité.
void homer::World::Remove(const std::string& name)
{
    auto _entityToDelete = Find(name);
    if (_entityToDelete != nullptr)
    {
        for (auto entity : m_EntityToDelete)
        {
            if (entity == _entityToDelete)
            {
                return;
            }
        }
        m_EntityToDelete.emplace_back(_entityToDelete);
    }
}

//Trouve et retourne une entité en utilisant son nom.
homer::Entity* homer::World::Find(const std::string& name)
{
    if (m_EntityMap.count(name) > 0)
    {
        return m_EntityMap[name];
    }

    return nullptr;
}

//Charge une scene.
void homer::World::Load(const std::string& scene) 
{
    if (m_Scenes.count(scene) > 0) 
    {
        m_SceneToLoad = scene;
    }
}

void homer::World::UpdateLoadScene()
{
    if (!m_SceneToLoad.empty())
    {
        Unload();
        m_Scenes[m_SceneToLoad]->Load();
        m_CurrentScene = m_SceneToLoad;
        m_SceneToLoad.clear();
    }
}

//Décharge une scène et les entités qu'elle contient.
void homer::World::Unload()
{
    for (auto entity : m_EntityInWorld) 
    {
        entity->Destroy();
        delete entity;
    }

    for (auto entity : m_EntityToStart)
    {
        entity->Destroy();
        delete entity;
    }

    for (auto entity : m_EntityToDelete)
    {
        delete entity;
    }
    if(!m_CurrentScene.empty())
        m_Scenes[m_CurrentScene]->ClearSpawner();
    Engine::Get().Collisions().Clear();
    Engine::Get().Audio().StopMusic();
    m_EntityToStart.clear();
    m_EntityInWorld.clear();
    m_EntityMap.clear();
    m_EntityToDelete.clear();
}

//Enregistre une scène.
void homer::World::Register(const std::string& name, IScene* scene) 
{
    if (m_Scenes.count(name) == 0) 
    {
        m_Scenes[name] = scene;
        int s = static_cast<int>(m_ScenesOrder.size());
        m_ScenesOrder[s] = name;
    }
}

//Retire toutes les scènes existantes.
void homer::World::Unregister()
{
    m_CurrentScene = "";
    for (auto scene : m_Scenes)
    {
        delete scene.second;
    }
    m_Scenes.clear();
}

homer::IScene* homer::World::GetCurrentScene()
{
    return m_Scenes[m_CurrentScene];
}

int homer::World::GetGravity()
{
    return m_Gravity;
}

std::string homer::World::GetScore()
{
    return std::to_string(m_Score);
}

void homer::World::AddScore(int points)
{
    m_Score += points;
}

void homer::World::ResetScore()
{
    m_Score = 0;
}

void homer::World::NextStage()
{
    for (auto name : m_ScenesOrder)
    {
        if (name.second == m_CurrentScene)
        {
            if (name.first == m_ScenesOrder.size() - 1)
            {
                ResetScore();
                Load("Title");
            }
            else
            {
                Load(m_ScenesOrder[name.first + 1]);
            }
            break;
        }
    }
}

void homer::World::SetNumberEnemies(int enemies)
{
    m_Enemies = enemies;
}

void homer::World::EnemyDefeated()
{
    m_Enemies -= 1;
    if (m_Enemies == 0)
    {
        DoDelete();
        NextStage();
    }
}

