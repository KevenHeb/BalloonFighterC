#include <Tilemap.h>
#include <Engine.h>

homer::Tilemap::Tilemap(Entity* parent) : Component(parent)
{
}

void homer::Tilemap::Load(const std::string& filename, int mapWidth, int mapHeight, int tileWidth, int tileHeight)
{
    auto& graphics = Graphics();
    m_TilesetId = graphics.LoadTexture(filename);
    m_TileWidth = tileWidth;
    m_TileHeight = tileHeight;
    m_Width = mapWidth;
    m_Height = mapHeight;

    int _w, _h;
    graphics.GetTextureSize(m_TilesetId, &_w, &_h);

    int _tilePerRow = _w / m_TileWidth;
    int _tilePerCol = _h / m_TileHeight;
    int _tileCount = _tilePerRow * _tilePerCol;

    for (int i = 0; i < _tileCount; i++)
    {
        int _ty = i / _tilePerRow;
        int _tx = i - _ty * _tilePerRow;

        RectI _tile = {
            _tx * m_TileWidth,
            _ty * m_TileHeight,
            m_TileWidth,
            m_TileHeight
        };

        m_Tileset.push_back(_tile);
    }
}

void homer::Tilemap::AddLayer(const std::string& layer, TLayer tiles)
{
    if (m_Tilemap.count(layer) == 0)
    {
        m_Tilemap.emplace(layer, tiles);
    }
}

homer::TLayer homer::Tilemap::GetLayer(const std::string& name)
{
    if (m_Tilemap.count(name) > 0)
    {
        return m_Tilemap[name];
    }

    return TLayer{};
}

int Clamp(int value, const int min, const int max)
{
    if (value < min)
    {
        value = min;
    }
    else if (value > max)
    {
        value = max;
    }

    return value;
}

bool homer::Tilemap::IsColliding(const std::string& layer, float x, float y, float w, float h, int* tileIndex)
{
    const int tLeftTile = Clamp(static_cast<int>(x / m_TileWidth), 0, m_Width);
    const int tRightTile = Clamp(static_cast<int>((x + w) / m_TileWidth), 0, m_Width);
    const int tTopTile = Clamp(static_cast<int>(y / m_TileHeight), 0, m_Height);
    const int tBottomTile = Clamp(static_cast<int>((y + h) / m_TileHeight), 0, m_Height);

    for (int i = tLeftTile; i <= tRightTile; i++)
    {
        for (int j = tTopTile; j <= tBottomTile; j++)
        {
            if (i < m_Width && j < m_Height)
            {
                if (m_Tilemap[layer][j][i] != 0)
                {
                    *tileIndex = m_Tilemap[layer][j][i];
                    return true;
                    break;
                }
            }
        }
    }

    *tileIndex = -1;
    return false;
}

void homer::Tilemap::Draw()
{
    for (auto layer : m_Tilemap)
    {
        for (int y = 0; y < m_Height; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                int _tileIdx = layer.second[y][x];

                if (_tileIdx > 0)
                {
                    _tileIdx -= 1;
                    int _w = m_TileWidth * m_ScaleFactor;
                    int _h = m_TileHeight * m_ScaleFactor;
                    RectF _dst = {
                        static_cast<float>(x * _w),
                        static_cast<float>(y * _h),
                        static_cast<float>(_w),
                        static_cast<float>(_h)
                    };

                    Graphics().DrawTexture(
                        m_TilesetId, m_Tileset[_tileIdx],
                        _dst, 0.0, { false, false }, Color::WHITE);
                }
            }
        }
    }
}