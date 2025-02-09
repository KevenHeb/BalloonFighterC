#pragma once
#include <ICollision.h>
#include <map>
#include <vector>

namespace homer
{
    //Fonction du prof
    class Collision : public ICollision
    {
    public:

        /**
        * Vérifie les collisions entre un cercle et un point
        * <params> px, py : position du point
        * <params> cx, cy : position du cercle
        * <param> cr : radian du cercle
        */
        virtual bool CollisionPointCircle(float px, float py, float cx, float cy, float cr) override;

        /**
        * Vérifie les collisions entre deux cercle
        * <params> cx1, cy1 : position du premier cercle
        * <params> cx2, cy2 : position du deuxieme cercle
        * <params> cr1, cr2 : radian des cercles
        */
        virtual bool CollisionCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) override;

        /**
        * Vérifie les collisions entre un point et un rectangle
        * <params> px, py : position du point
        * <params> rx, ry : position du rectangle
        * <params> rw, rh : dimension du rectangle
        */
        virtual bool CollisionPointRect(float px, float py, float rx, float ry, float rw, float rh) override;

        /**
        * Vérifie les collisions entre deux rectangles
        * <params> rx1, ry1, rx2, ry2 : position des rectangles
        * <params> rw1, rh1, rw2, rh2 : dimension des rectangles
        */
        virtual bool CollisionRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) override;

        /**
        * Vérifie les collisions entre un cercle et un rectangle
        * <params> rx, ry : position du rectangle
        * <params> rw, rh : dimension du rectangle
        * <params> cx, cy : position du cercle
        * <param> cr : radian du cercle
        */
        virtual bool CollisionRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr) override;

        /**
        * Ajoute a une liste de CollisionLayers l'entité recue
        * <param> layerName : le nom de la layer que l'entité doit être assigné
        * <param> entity : l'entité a assigné
        */
        virtual void AddToLayer(const std::string& layerName, Entity* entity) override;

        /**
        * Regarde si l'entité est en collisions avec des entité dans la layer.
        * Retourne vrai si il y a collision
        * <param> entity : l'entité que l'on vérifie la collision
        * <param> layerName : le nom de la layer que l'entité doit être assigné
        * <param> other : retourn le pointeur d'une entité de la layer si elle est en collision avec la premiere.
        */
        virtual bool CollideWithLayer(Entity* entity, const std::string& layerName, Entity** other) override;

        /**
        * Retire l'entité recue des layers.
        * <param> entity : l'entité a retirer.
        */
        virtual void Remove(Entity* entity) override;

        //Vide entierement la liste des layers.
        virtual void Clear() override;

    private:
        std::map<std::string, std::vector<Entity*>> m_Layers;
    };
}