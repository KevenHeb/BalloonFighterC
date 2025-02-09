#pragma once
#include "Atlas.h"
#include "Animation.h"

namespace homer
{
    class IPrefab
    {
    public:
        //Cr�er et retourne une entit� avec des composants et des donn�es pr�parer d'avance.
        virtual Entity* Clone() = 0;

    protected:
        int m_Cloned = 0;
    };
}