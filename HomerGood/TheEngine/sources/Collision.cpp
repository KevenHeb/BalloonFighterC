#include <Collision.h>
#include <math.h>
#include <Entity.h>

bool homer::Collision::CollisionPointCircle(float px, float py, float cx, float cy, float cr)
{
    float vecX = px - cx;
    float vecY = py - cy;
    float d = sqrtf((vecX * vecX) + (vecY * vecY));

    return d <= cr;
}

bool homer::Collision::CollisionCircles(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
    float vecX = c1x - c2x;
    float vecY = c1y - c2y;
    float d = sqrtf((vecX * vecX) + (vecY * vecY));

    return d <= (c1r + c2r);
}

bool homer::Collision::CollisionPointRect(float px, float py, float rx, float ry, float rw,
    float rh)
{
    return px >= rx && py >= ry && px <= (rx + rw) && py <= (ry + rh);
}

bool homer::Collision::CollisionRects(float r1x, float r1y, float r1w, float r1h, float r2x,
    float r2y, float r2w, float r2h)
{
    return (r1x <= (r2x + r2w) && (r1x + r1w) >= r2x &&
        r1y <= (r2y + r2h) && (r1y + r1h) >= r2y);
}

bool homer::Collision::CollisionRectCircle(float rx, float ry, float rw, float rh, float cx, float cy, float cr)
{
    if (CollisionPointRect(cx, cy, rx, ry, rw, rh))
    {
        return true;
    }

    float tx = cx;
    float ty = cy;

    if (tx < rx) tx = rx;
    if (tx > rx + rw) tx = rx + rw;
    if (ty < ry) ty = ry;
    if (ty > ry + rh) ty = ry + rh;

    return CollisionPointCircle(tx, ty, cx, cy, cr);
}

void homer::Collision::AddToLayer(const std::string& layerName, Entity* entity)
{
    if (m_Layers.count(layerName) == 0)
    {
        m_Layers.emplace(layerName, std::vector<Entity*>());
    }

    m_Layers[layerName].push_back(entity);
}

bool homer::Collision::CollideWithLayer(Entity* entity, const std::string& layerName, Entity** other)
{
    if (m_Layers.count(layerName) > 0)
    {
        float rect1_x, rect1_y, rect1_w, rect1_h;
        float rect2_x, rect2_y, rect2_w, rect2_h;

        entity->GetPosition(&rect1_x, &rect1_y);
        entity->GetSize(&rect1_w, &rect1_h);

        for (Entity* e : m_Layers[layerName])
        {
            e->GetPosition(&rect2_x, &rect2_y);
            e->GetSize(&rect2_w, &rect2_h);

            if (CollisionRects(rect1_x, rect1_y, rect1_w, rect1_h, rect2_x, rect2_y, rect2_w, rect2_h))
            {
                *other = e;
                return true;
            }
        }
    }
    
    return false;
}

void homer::Collision::Remove(Entity* entity)
{
    for (auto layer : m_Layers)
    {
        std::vector<Entity*>::iterator it = layer.second.begin();
        while (it != layer.second.end())
        {
            if (*it == entity)
            {
                layer.second.erase(it);
                return;
            }

            it++;
        }
    }
}

void homer::Collision::Clear()
{
    m_Layers.clear();
}
