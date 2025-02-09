#pragma once
namespace homer
{
    class Entity;
    class IInput;
    class ILogger;
    class IGraphics;
    class IAudio;
    class IWorld;
    class ICollision;

    class Component
    {
    public:
        Component(Entity* parent);
        virtual ~Component() = default;

        //Methode Start de base de chaque components
        virtual void Start() {}
        //Methode Destroy de base de chaque components
        virtual void Destroy() {}
        //Methode qui retourne l'entité parent du component
        virtual Entity* GetParentEntity();

    protected:
        //Groupe de subclass qui retourne les fonctions de l'engin.
        //Retourne la fonction Exit de l'engin.
        void Exit();
        //Retourne le systeme Input de l'engin.
        IInput& Input() const;
        //Retourne le systeme Logger de l'engin.
        ILogger& Logger() const;
        //Retourne le systeme Graphic de l'engin.
        IGraphics& Graphics() const;
        //Retourne le systeme Audio de l'engin.
        IAudio& Audio() const;
        //Retourne le World de l'engin.
        IWorld& WorldService() const;
        //Retourne le systeme de collision de l'engin.
        ICollision& Collisions() const;

        Entity* m_Entity = nullptr;
    };
}