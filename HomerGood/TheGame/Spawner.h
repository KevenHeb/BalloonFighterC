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

    //Class qui spawn des pr�fab. 
    class Spawner : public Observer<RectF>
    {
    public:
        //Initialise des pr�fabs
        void Init();
        
        //Rajoute des pr�fabs a la liste.
        //<param> name : le nom du pr�fab
        //<param> prefab : le pr�fab a rajouter
        void AddPrefab(const std::string& name, IPrefab* prefab);

        //Vide la liste des pr�fabs
        void ClearPrefabs();

        //Appele la m�thode clone d'un pr�fab, et retourne l'entit� recue.
        //<param> name : le nom du pr�fab � cloner.
        Entity* Spawn(const std::string& name);

        //Ce OnNotify est appel� quand un ennemie est d�truit et clone une pr�fab Bubble via la m�thode Spawn.
        //<param> rect : la position et la dimension de la Bubble.s
        void OnNotify(const RectF& rect) override;
    private:
        TProtoMap m_PrefabMap;
    };
}