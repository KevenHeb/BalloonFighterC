#pragma once
#include "Atlas.h"
#include "Animation.h"

namespace homer
{
    class IPrefab
    {
    public:
        //Créer et retourne une entité avec des composants et des données préparer d'avance.
        virtual Entity* Clone() = 0;

    protected:
        int m_Cloned = 0;
    };
}