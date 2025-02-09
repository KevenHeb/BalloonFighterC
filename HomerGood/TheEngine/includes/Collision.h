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
        * V�rifie les collisions entre un cercle et un point
        * <params> px, py : position du point
        * <params> cx, cy : position du cercle
        * <param> cr : radian du cercle
        */
        virtual bool CollisionPointCircle(float px, float py, float cx, float cy, float cr) override;

        /**
        * V�rifie les collisions entre deux cercle
        * <params> cx1, cy1 : position du premier cercle
        * <params> cx2, cy2 : position du deuxieme cercle
        * <params> cr1, cr2 : radian des cercles
        */
        virtual bool CollisionCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) override;

        /**
        * V�rifie les collisions entre un point et un rectangle
        * <params> px, py : position du point
        * <params> rx, ry : position du rectangle
        * <params> rw, rh : dimension du rectangle
        */
        virtual bool CollisionPointRect(float px, float py, float rx, float ry, float rw, float rh) override;

        /**
        * V�rifie les collisions entre deux rectangles
        * <params> rx1, ry1, rx2, ry2 : position des rectangles
        * <params> rw1, rh1, rw2, rh2 : dimension des rectangles
        */
        virtual bool CollisionRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) override;

        /**
        * V�rifie les collisions entre un cercle et un rectangle
        * <params> rx, ry : position du rectangle
        * <params> rw, rh : dimension du rectangle
        * <params> cx, cy : position du cercle
        * <param> cr : radian du cercle
        */
        virtual bool CollisionRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr) override;

        /**
        * Ajoute a une liste de CollisionLayers l'entit� recue
        * <param> layerName : le nom de la layer que l'entit� doit �tre assign�
        * <param> entity : l'entit� a assign�
        */
        virtual void AddToLayer(const std::string& layerName, Entity* entity) override;

        /**
        * Regarde si l'entit� est en collisions avec des entit� dans la layer.
        * Retourne vrai si il y a collision
        * <param> entity : l'entit� que l'on v�rifie la collision
        * <param> layerName : le nom de la layer que l'entit� doit �tre assign�
        * <param> other : retourn le pointeur d'une entit� de la layer si elle est en collision avec la premiere.
        */
        virtual bool CollideWithLayer(Entity* entity, const std::string& layerName, Entity** other) override;

        /**
        * Retire l'entit� recue des layers.
        * <param> entity : l'entit� a retirer.
        */
        virtual void Remove(Entity* entity) override;

        //Vide entierement la liste des layers.
        virtual void Clear() override;

    private:
        std::map<std::string, std::vector<Entity*>> m_Layers;
    };
}