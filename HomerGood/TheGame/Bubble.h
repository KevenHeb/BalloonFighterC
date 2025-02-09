#pragma once
#include "BubbleComponent.h"
#include "IPrefab.h"

namespace homer
{
    //Prefab de bulle
    class Bubble : public IPrefab
    {
    public:
        //Voir IPrefab
        virtual Entity* Clone() override;
    };
}