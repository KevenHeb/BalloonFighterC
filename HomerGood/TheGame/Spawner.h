#pragma once
#include <map>
#include <string>
#include "Observer.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Bubble.h"

namespace homer
{
    typedef std::map<std::string, IPrefab*> TProtoMap;

    //Class qui spawn des préfab. 
    class Spawner : public Observer<RectF>
    {
    public:
        //Initialise des préfabs
        void Init();
        
        //Rajoute des préfabs a la liste.
        //<param> name : le nom du préfab
        //<param> prefab : le préfab a rajouter
        void AddPrefab(const std::string& name, IPrefab* prefab);

        //Vide la liste des préfabs
        void ClearPrefabs();

        //Appele la méthode clone d'un préfab, et retourne l'entité recue.
        //<param> name : le nom du préfab à cloner.
        Entity* Spawn(const std::string& name);

        //Ce OnNotify est appelé quand un ennemie est détruit et clone une préfab Bubble via la méthode Spawn.
        //<param> rect : la position et la dimension de la Bubble.s
        void OnNotify(const RectF& rect) override;
    private:
        TProtoMap m_PrefabMap;
    };
}