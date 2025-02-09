#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <Engine.h>
#include "TitleScene.h"
#include "StageOne.h"
#include "StageTwo.h"

#if _DEBUG
#include <vld.h>
#endif

void InitGameplay()
{
    homer::Engine::Get().Logger().LogMessage("Starting game");
    homer::Engine::Get().WorldService().Register("Title", new homer::TitleScene());
    homer::Engine::Get().WorldService().Register("Stage1", new homer::StageOne());
    homer::Engine::Get().WorldService().Register("Stage2", new homer::StageTwo());
}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
    homer::Engine& engine = homer::Engine::Get();

    if (engine.Init("Balloon Fight", 800, 600))
    {
        InitGameplay();
        engine.Get().WorldService().Load("Title");
        homer::Engine::Get().Start();
    }

    return 0;
}