#pragma once
#include <IWorld.h>
#include <IScene.h>

namespace homer
{
    class World : public IWorld
    {
    public:
        virtual ~World();

        void StartEntities() override;
        void Update(float dt) override;
        void Draw() override;
        Entity* Create(const std::string& name) override;
        void DoDelete() override;

        //Retire toute les entitées de la scene.
        void RemoveAllEntities() override;
        void Remove(const std::string& name) override;
        Entity* Find(const std::string& name) override;
        void Load(const std::string& scene) override;
        void UpdateLoadScene() override;
        void Unload() override;
        void Register(const std::string& name, IScene* scene) override;
        void Unregister() override;

        //Retourne la scene courante.
        IScene* GetCurrentScene() override;

        //Retourne la variable de gravité
        int GetGravity() override;

        //Retourne le score du joueur.
        std::string GetScore() override;

        //Ajoute des points au score.
        //<param> points : les point a ajouter.
        void AddScore(int points) override;

        //Retourne le score a zéro.
        void ResetScore() override;

        //Change de scene pour la prochaine dans la liste.
        //Si il y en a pas, change de scene pour la premiere dans la liste (title screen).
        void NextStage() override;

        //Indique au monde le nombre d'ennemie dans la scene.
        //<param> enemies : le nombre d'ennemie.
        void SetNumberEnemies(int enemies) override;

        //Appeler lorsqu'un ennemie est mort. Réduit la variable m_Enemies.
        //Si elle touche zéro, la fonction appele NextStage
        void EnemyDefeated() override;

    private:
        int m_Gravity = 3;
        int m_Score = 0;
        int m_Enemies = 255;
        std::map<std::string, Entity*> m_EntityMap;
        std::vector<Entity*> m_EntityInWorld;
        std::vector<Entity*> m_EntityToStart;
        std::vector<Entity*> m_EntityToDelete;
        std::map<std::string, IScene*> m_Scenes;
        std::map<int, std::string> m_ScenesOrder;
        std::string m_CurrentScene;
        std::string m_SceneToLoad;
    };

}