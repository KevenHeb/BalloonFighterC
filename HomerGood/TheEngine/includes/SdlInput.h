#pragma once

#include <IInput.h>

namespace homer
{
    class SdlInput final : public IInput
    {
    public:
        virtual ~SdlInput() = default;
        //Retourne vrai si la clé recue en paramêtre est enfoncer.
        //<param> keycode : le code de la clé à vérifier.
        virtual bool IsKeyDown(EKey keycode) override;

        //Retourne vrai si le bouton de la sourie recue en paramêtre est enfoncer.
        //<param> button : le numéro représentant le bouton de la sourie.
        virtual bool IsButtonDown(int button) override;

        //Retourne la position de la sourie via les parametres x et y.
        virtual void GetMousePosition(int* x, int* y) override;

    protected:
        //Methode Update
        virtual void Update() override;

    private:
        const unsigned char* m_KeyStates = nullptr;
        int m_MouseX = 0;
        int m_MouseY = 0;
        bool m_MouseStates[3]{ false, false, false };
    };
}