#pragma once
#include <string>
#include <vector>
#include <map>

namespace homer
{
    class Entity;
    class IScene;

    class IWorld
    {
    public:
        virtual ~IWorld() = default;

        virtual void StartEntities() = 0;
        virtual void Update(float dt) = 0;
        virtual void Draw() = 0;
        virtual Entity* Create(const std::string& name) = 0;
        virtual void DoDelete() = 0;
        virtual void RemoveAllEntities() = 0;
        virtual void Remove(const std::string& name) = 0;
        virtual Entity* Find(const std::string& name) = 0;
        virtual void Load(const std::string& scene) = 0;
        virtual void UpdateLoadScene() = 0;
        virtual void Unload() = 0;
        virtual void Register(const std::string& name, IScene* scene) = 0;
        virtual void Unregister() = 0;
        virtual IScene* GetCurrentScene() = 0;
        virtual int GetGravity() = 0;
        virtual std::string GetScore() = 0;
        virtual void AddScore(int points) = 0;
        virtual void ResetScore() = 0;
        virtual void NextStage() = 0;
        virtual void SetNumberEnemies(int enemies) = 0;
        virtual void EnemyDefeated() = 0;
        //virtual void Shutdown() = 0;
    };

}