#ifndef SOUND_HPP
#define SOUND_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <string>

namespace Particule::Api
{
    class Sound
    {
    public:
        Sound() {};
        Sound(Resource path){ (void)path; }
        Sound(const Sound& other){ (void)other; }
        Sound& operator=(const Sound& other){ (void)other; return *this; }
        ~Sound(){};

        constexpr void Play(){};
        constexpr void Pause(){};
        constexpr void Stop(){};
        constexpr void SetVolume(float volume){ (void)volume; };
        constexpr void SetPitch(float pitch){ (void)pitch; };
        constexpr void SetLoop(bool loop){ (void)loop; };
        constexpr void SetPosition(float position){ (void)position; };
        constexpr void SetPlayingOffset(float time){ (void)time; };
        
        constexpr float GetVolume(){ return 0.0f; };
        constexpr float GetPitch(){ return 0.0f; };
        constexpr bool GetLoop(){ return false; };
        constexpr float GetPosition(){ return 0.0f; };
        constexpr float GetPlayingOffset(){ return 0.0f; };
        constexpr float GetDuration(){ return 0.0f; };

        constexpr bool IsPlaying(){ return false; };
        constexpr bool IsPaused(){ return false; };
        constexpr bool IsStopped(){ return false; };
        constexpr bool IsLooping(){ return false; };
    };
}
#endif // SOUND_HPP