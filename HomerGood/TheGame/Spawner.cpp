#include "Spawner.h"
#include "Entity.h"

void homer::Spawner::Init()
{
    Enemy* prefabEnemy = new Enemy();
    AddPrefab("Enemy", prefabEnemy);
    Bubble* prefabBubble = new Bubble();
    AddPrefab("Bubble", prefabBubble);
}

void homer::Spawner::AddPrefab(const std::string& name, IPrefab* prefab)
{
    if (m_PrefabMap.count(name) == 0)
    {
        m_PrefabMap.emplace(name, prefab);
    }    
}

void homer::Spawner::ClearPrefabs()
{
    for (auto prefab : m_PrefabMap)
    {
        delete prefab.second;
    }
    m_PrefabMap.clear();
}

homer::Entity* homer::Spawner::Spawn(const std::string& name)
{
    if (m_PrefabMap.count(name) > 0)
    {
        Entity* _clone = m_PrefabMap[name]->Clone();
        if (name == "Enemy")
        {
            _clone->GetComponent<EnemyController>()->OnDestroy.AddListener(this);
        }
        return _clone;
    }
    return nullptr;
}

void homer::Spawner::OnNotify(const RectF& rect)
{
    Entity* bubble = Spawn("Bubble");
    bubble->SetPosition(rect);
    bubble->SetSize(rect.w, rect.h * 0.5f);
}
