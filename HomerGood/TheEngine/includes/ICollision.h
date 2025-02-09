#pragma once
#include <string>

namespace homer
{
    class Entity;

    class ICollision
    {
    public:
        virtual ~ICollision() = default;

        virtual bool CollisionPointCircle(float px, float py, float cx, float cy, float cr) = 0;
        virtual bool CollisionCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r) = 0;
        virtual bool CollisionPointRect(float px, float py, float rx, float ry, float rw, float rh) = 0;
        virtual bool CollisionRects(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h) = 0;
        virtual bool CollisionRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr) = 0;

        virtual void AddToLayer(const std::string& layerName, Entity* entity) = 0;
        virtual bool CollideWithLayer(Entity* entity, const std::string& layerName, Entity** other) = 0;
        virtual void Remove(Entity* entity) = 0;
        virtual void Clear() = 0;
    };
}