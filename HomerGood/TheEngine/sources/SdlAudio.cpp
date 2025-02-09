#include <SdlAudio.h>
#include <SDL_mixer.h>
#include <Engine.h>

homer::SdlAudio::SdlAudio()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
}

homer::SdlAudio::~SdlAudio()
{
    Mix_CloseAudio();
}

size_t homer::SdlAudio::LoadMusic(const std::string& filename)
{
    const size_t _musId = std::hash<std::string>()(filename);
    if (m_MusicCache.count(_musId) > 0)
    {
        return _musId;
    }

    Mix_Music* _mus = Mix_LoadMUS(filename.c_str());
    if (_mus)
    {
        m_MusicCache.emplace(_musId, _mus);
        return _musId;
    }

    homer::Engine::Get().Logger().LogMessage("Error with music: " + filename);
    homer::Engine::Get().Logger().LogMessage(Mix_GetError());

    return 0;
}

size_t homer::SdlAudio::LoadSound(const std::string& filename)
{
    const size_t _sfxId = std::hash<std::string>()(filename);
    if (m_SoundCache.count(_sfxId) > 0)
    {
        return _sfxId;
    }

    Mix_Chunk* _sfx = Mix_LoadWAV(filename.c_str());
    if (_sfx)
    {
        m_SoundCache.emplace(_sfxId, _sfx);
        return _sfxId;
    }

    homer::Engine::Get().Logger().LogMessage("Error with sfx: " + filename);
    homer::Engine::Get().Logger().LogMessage(Mix_GetError());
    return 0;
}

void homer::SdlAudio::PlayMusic(size_t id)
{
    PlayMusic(id, -1);
}

void homer::SdlAudio::PlayMusic(size_t id, int loop)
{
    Mix_PlayMusic(m_MusicCache[id], loop);
}

void homer::SdlAudio::PlaySFX(size_t id)
{
    PlaySFX(id, 0);
}

void homer::SdlAudio::PlaySFX(size_t id, int loop)
{
    Mix_PlayChannel(-1, m_SoundCache[id], loop);
}

void homer::SdlAudio::PauseMusic()
{
    Mix_PauseMusic();
}

void homer::SdlAudio::StopMusic()
{
    Mix_HaltMusic();
}

void homer::SdlAudio::ResumeMusic()
{
    Mix_ResumeMusic();
}

void homer::SdlAudio::SetVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

void homer::SdlAudio::SetVolume(size_t soundId, int volume)
{
    Mix_VolumeChunk(m_SoundCache[soundId], volume);
}