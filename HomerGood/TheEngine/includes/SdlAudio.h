#pragma once
#include <IAudio.h>
#include <map>

struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

namespace homer
{
    class SdlAudio : public IAudio
    {
    public:
        SdlAudio();
        virtual ~SdlAudio();

        //Charge un fichier de music et retourne son numero d'identification.
        //<param> filename : le nom du fichier
        virtual size_t LoadMusic(const std::string& filename) override;

        //Charge un fichier de son et retourne son numero d'identification.
        //<param> filename : le nom du fichier
        virtual size_t LoadSound(const std::string& filename) override;

        //Joue une musique en loop continue.
        //<param> id : le numero d'identification de la musique a jouer.
        virtual void PlayMusic(size_t id) override;

        //Joue une musique le nombre de foi demander.
        //<param> id : le numero d'identification de la musique a jouer.
        virtual void PlayMusic(size_t id, int loop) override;

        //Joue un effet sonore une foi.
        //<param> id : le numero d'identification du son a jouer.
        virtual void PlaySFX(size_t id) override;
        
        //Joue un effet le nombre de foi demander.
        //<param> id : le numero d'identification du son a jouer.
        virtual void PlaySFX(size_t id, int loop) override;

        //Pause la musique.
        virtual void PauseMusic() override;

        //Arrete de jouer la musique.
        virtual void StopMusic() override;

        //Recommence la musique précédement mis sur pause.
        virtual void ResumeMusic() override;

        //Ajuste le volume de l'application.
        //<param> id : le numero d'identification de la musique a jouer.
        virtual void SetVolume(int volume) override;

        //Ajuste le volume de la musique ou le son spécifier.
        //<param> id : le numero d'identification de la musique ou du son a ajuster.
        virtual void SetVolume(size_t soundId, int volume) override;

    private:
        typedef std::map<size_t, Mix_Chunk*> TChunkMap;
        typedef std::map<size_t, Mix_Music*> TMusicMap;

        TChunkMap m_SoundCache;
        TMusicMap m_MusicCache;
    };
}
