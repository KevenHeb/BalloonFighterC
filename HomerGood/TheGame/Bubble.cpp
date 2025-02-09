#include "Bubble.h"
#include "Engine.h"
#include "Entity.h"
#include "BubbleComponent.h"


homer::Entity* homer::Bubble::Clone()
{
    Entity* bubble = Engine::Get().WorldService().Create("Bubble" + m_Cloned);
    bubble->AddComponent<Atlas>()->SetId("Assets/bubble.png");
    bubble->GetComponent<Atlas>()->AddFrame("Bubble", 0, 0, 16, 16);
    bubble->GetComponent<Atlas>()->SetFrame("Bubble");
    bubble->AddComponent<BubbleComponent>();

    m_Cloned += 1;
    return bubble;
}
