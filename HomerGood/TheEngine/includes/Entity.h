#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "IDrawable.h"
#include "IUpdatable.h"
#include <map>
#include "RectF.h"

namespace homer
{
    class Entity final
    {
    public:
        Entity(const std::string& name);
        Entity(const std::string& name, RectF dst);
        virtual ~Entity() = default;

        virtual void Start();
        virtual void Update(float dt);
        virtual void Draw();
        virtual void Destroy();

        virtual void SetPosition(RectF dst);
        virtual void SetPosition(float x, float y);
        virtual void SetSize(float w, float h);
        virtual void Move(int x, int y);

        std::string& GetName();
        
        RectF GetPosition();
        void GetPosition(float* x, float* y);
        void GetSize(float* w, float* h);
        float GetX();
        float GetY();
        float GetW();
        float GetH();
            
        //Methode qui attache un component à une entité
        template<typename T>
        T* AddComponent()
        {
            T* component = new T(this);
            const type_info* type = &typeid(*component);
            if (m_ComponentByType.count(type) == 0)
            {
                m_ComponentByType.emplace(type, component);
                m_AllComponents.emplace_back(component);

                auto _updatable = dynamic_cast<IUpdatable*>(component);
                if (_updatable != nullptr)
                {
                    m_ComponentToUpdate.emplace_back(_updatable);
                }

                auto _drawable = dynamic_cast<IDrawable*>(component);
                if (_drawable != nullptr)
                {
                    m_ComponentToDraw.emplace_back(_drawable);
                }

                return component;
            }
            delete component;
            return nullptr;
        };

        //Methode qui retourne un component d'une entité si elle existe.
        template<typename T>
        T* GetComponent()
        {
            const type_info* _key = &typeid(T);
            if (m_ComponentByType.count(_key) > 0)
            {
                return static_cast<T*>(m_ComponentByType[_key]);
            }
            return nullptr;
        };

    protected:
        friend class World;
        std::string m_Name;
        RectF m_Position;

        std::vector<Component*> m_AllComponents;
        std::vector<IUpdatable*> m_ComponentToUpdate;
        std::vector<IDrawable*> m_ComponentToDraw;
        std::map<const type_info*, Component*> m_ComponentByType;
    };
}