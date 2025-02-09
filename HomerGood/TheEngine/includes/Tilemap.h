#pragma once
#include <vector>
#include <map>
#include <string>
#include <RectI.h>
#include <Component.h>
#include <IDrawable.h>

namespace homer
{
    typedef std::vector<std::vector<int>> TLayer;
    typedef std::map<std::string, TLayer> TTilemap;
    typedef std::vector<RectI> TTileset;

    class Tilemap : public Component, public IDrawable
    {
    public:
        virtual ~Tilemap() = default;
        Tilemap(Entity* parent);

        //Draw function
        virtual void Draw() override;

        /**
        * Charge les informations tilemap recue en parametre.
        * <param> filename : nom du fichier contenant les informations des tuiles de la tilemap.
        * <params> mapWidth, mapHeight : la taille de la map.
        * <params> tileWidth, tileHeight : la taille des tuiles.
        */
        void Load(const std::string& filename, int mapWidth, int mapHeight, int tileWidth, int tileHeight);

        /**
        * Rajoute une layer à la tilemap.
        * <param> layer : le nom de la layer à ajouter.
        * <param> tiles : liste de l'index des tiles.
        */
        void AddLayer(const std::string& layer, TLayer tiles);

        /**
        * Retourn la liste de tuile de la layer spécifier.
        * <param> name : le nom de la layer.
        */
        TLayer GetLayer(const std::string& name);
        /**
        * Retourne vrai si il ya collision de la layer avec un objet.
        * Retourn aussi l'index de la tuile en collision.
        * <param> name : le nom de la layer.
        * <params> x, y, w, h : la position et dimension de l'objet.
        * <param> tileIndex : l'index de la tuile en collision, si il y en a.
        */
        bool IsColliding(const std::string& layer, float x, float y, float w, float h, int* tileIndex);

    private:
        TTilemap m_Tilemap;
        int m_Width = 0;
        int m_Height = 0;
        size_t m_TilesetId = 0;
        int m_TileWidth = 0;
        int m_TileHeight = 0;
        TTileset m_Tileset;
        int m_ScaleFactor = 1;
    };
}