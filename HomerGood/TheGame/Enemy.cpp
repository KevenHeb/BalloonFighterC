#include "Enemy.h"
#include "Engine.h"
#include "Entity.h"

homer::Entity* homer::Enemy::Clone()
{
    Entity* enemy = Engine::Get().WorldService().Create("Enemy" + std::to_string(m_Cloned));
    enemy->AddComponent<Atlas>()->AddFrame("Default", 0, 0, 16, 32);
    enemy->GetComponent<Atlas>()->SetFrame("Default");
    enemy->GetComponent<Atlas>()->SetId("Assets/enemy_sheet.png");

    enemy->AddComponent<Animation>()->InitAnimation(4, 16, 32);
    enemy->GetComponent<Animation>()->AddClip("Pump", 0, 0, 8, 0.5f);
    enemy->GetComponent<Animation>()->AddClip("Fly", 2, 0, 4, 0.25f);
    enemy->GetComponent<Animation>()->AddClip("Fall", 3, 0, 2, 0.10f);
    enemy->AddComponent<EnemyController>();

    m_Cloned += 1;
    return enemy;
}
