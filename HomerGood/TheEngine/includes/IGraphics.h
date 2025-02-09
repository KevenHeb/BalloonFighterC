#pragma once
#include <string>
#include <vector>
#include <RectI.h>
#include <RectF.h>
#include <Color.h>
#include <Flip.h>

typedef std::vector<std::vector<int>> TLayer;
typedef std::vector<homer::RectI> TTileset;

namespace homer
{
    //Methode du prof.
    class IGraphics
    {
    public:
        virtual ~IGraphics() = default;

        virtual bool Initialize(const std::string& title, int w, int h) = 0;
        virtual void Shutdown() = 0;
        virtual void SetColor(uchar r, uchar g, uchar b, uchar a) = 0;
        virtual void SetColor(const Color& color) = 0;
        virtual void Clear() = 0;
        virtual void Present() = 0;
        virtual void DrawRect(float x, float y, float w, float h, const Color& color) = 0;
        virtual void DrawRect(const RectF& rect, const Color& color) = 0;
        virtual void FillRect(float x, float y, float w, float h, const Color& color) = 0;
        virtual void FillRect(const RectF& rect, const Color& color) = 0;
        virtual void DrawLine(float x1, float y1, float x2, float y2, const Color& color) = 0;
        virtual size_t LoadTexture(const std::string& filename) = 0;
        virtual void DrawTexture(size_t id, const RectI& src, const RectF& dst, double angle, const Flip& flip, const Color& color) = 0;
        virtual void DrawTexture(size_t id, const RectF& dst, const Color& color) = 0;
        virtual void DrawTexture(size_t id, const Color& color) = 0;
        virtual void GetTextureSize(size_t id, int* w, int* h) = 0;
        virtual size_t LoadFont(const std::string& filename, int fontSize) = 0;
        virtual void DrawString(const std::string& text, size_t fontId, float x, float y, const Color& color) = 0;
        virtual void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) = 0;
    };
}