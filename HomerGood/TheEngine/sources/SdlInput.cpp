#include <SdlInput.h>
#include <SDL.h>
#include <Engine.h>

void homer::SdlInput::Update()
{
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
        switch (_event.type)
        {
        case SDL_QUIT:
            Engine::Get().Exit();
            break;

        case SDL_MOUSEBUTTONDOWN:
            SDL_MouseButtonEvent _buttonDown = _event.button;
            m_MouseStates[_buttonDown.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            SDL_MouseButtonEvent _buttonUp = _event.button;
            m_MouseStates[_buttonUp.button] = true;
            break;

        case SDL_MOUSEMOTION:
            SDL_MouseMotionEvent _motion = _event.motion;
            m_MouseX = _motion.x;
            m_MouseY = _motion.y;
            break;

        case SDL_KEYUP:
        case SDL_KEYDOWN:
            m_KeyStates = SDL_GetKeyboardState(nullptr);
            break;
        }
    }
}

bool homer::SdlInput::IsKeyDown(EKey keycode)
{
    if (m_KeyStates != nullptr)
    {
        return m_KeyStates[static_cast<int>(keycode)] == 1;
    }

    return false;
}

bool homer::SdlInput::IsButtonDown(int button)
{
    return m_MouseStates[button];
}

void homer::SdlInput::GetMousePosition(int* x, int* y)
{
    *x = m_MouseX;
    *y = m_MouseY;
}