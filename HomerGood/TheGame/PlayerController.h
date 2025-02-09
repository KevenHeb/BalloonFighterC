#pragma once
#include "Character.h"
#include "IPlayerState.h"

namespace homer
{
    //Voir Character.h pour les fonction override.
    class PlayerController : public Character
    {
    public:
        PlayerController(Entity* parent);
        virtual ~PlayerController();
        virtual void Start() override;
        virtual void Update(float dt) override;
        void Hit() override;
        void ChangeState(const std::string& state) override;
        Animation* GetAnimation() override;

        //Ce gére de toute les collisions lier au joueur. Appeler chaque Update
        //<params> x, y : variable utileser pour certaine collision. Représente la position du joueur au début de l'update.
        void ManageCollisions(float x, float y);

        //Fonctions appelé lorsque le joueur saute.
        void Jump();

        //Retourne le nombre de balloon du joueur.
        int GetBalloons();
    private:
        float m_JumpVelocity = 0;
        int m_Balloons = 2;
        int m_Speed = 200;
        bool m_SpaceDown = true;
        bool m_Dead = false;
        bool m_Invincible = false;
        float m_InvTimer = 0.0f;
        size_t m_PopSFX;
        size_t m_FlySFX;
        //States
        IPlayerState* m_CurrentState = nullptr;
        std::map<std::string, IPlayerState*> m_States;
    };
}