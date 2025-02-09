#pragma once
#include <IGraphics.h>
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;

namespace homer
{
    class SdlGraphics : public IGraphics
    {
    public:
        virtual ~SdlGraphics() = default;
        virtual bool Initialize(const std::string& title, int w, int h) override;
        virtual void Shutdown() override;
        virtual void SetColor(uchar r, uchar g, uchar b, uchar a) override;
        virtual void SetColor(const Color& color) override;
        virtual void Clear() override;
        virtual void Present() override;
        virtual void DrawRect(float x, float y, float w, float h, const Color& color) override;
        virtual void DrawRect(const RectF& rect, const Color& color) override;
        virtual void FillRect(float x, float y, float w, float h, const Color& color) override;
        virtual void FillRect(const RectF& rect, const Color& color) override;
        virtual void DrawLine(float x1, float y1, float x2, float y2, const Color& color) override;
        virtual size_t LoadTexture(const std::string& filename) override;
        virtual void DrawTexture(size_t id, const RectI& src, const RectF& dst, double angle, const Flip& flip, const Color& color) override;
        virtual void DrawTexture(size_t id, const RectF& dst, const Color& color) override;
        virtual void DrawTexture(size_t id, const Color& color) override;
        virtual void GetTextureSize(size_t id, int* w, int* h) override;
        virtual size_t LoadFont(const std::string& filename, int fontSize) override;
        virtual void DrawString(const std::string& text, size_t fontId, float x, float y, const Color& color) override;
        virtual void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) override;

    private:
        void SetColorMode(size_t id, const Color& color);

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;

        typedef std::map<size_t, SDL_Texture*> TTextureMap;
        typedef std::map<size_t, TTF_Font*> TFontMap;

        TTextureMap m_TextureCache;
        TFontMap m_FontCache;
    };
}
