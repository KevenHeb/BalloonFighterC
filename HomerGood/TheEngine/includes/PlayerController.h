#pragma once
#include "Component.h"
#include "IUpdatable.h"

namespace homer
{
    class PlayerController : public Component, public IUpdatable
    {
    public:
        PlayerController(Entity* parent);
        //virtual ~Player() = default;
        virtual void Update(float dt) override;
        void Jump();
        void Hit();

    private:
        float m_JumpVelocity = 0;
        int m_Balloons = 2;
        int m_Speed = 2;
        //States
    };
}