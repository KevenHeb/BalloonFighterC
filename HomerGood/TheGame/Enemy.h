#pragma once
#include "EnemyController.h"
#include "IPrefab.h"

namespace homer
{
    //Préfab d'ennemie
    class Enemy : public IPrefab
    {
    public:
        virtual Entity* Clone() override;
    };
}