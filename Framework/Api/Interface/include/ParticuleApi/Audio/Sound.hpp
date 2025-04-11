#ifndef SOUND_HPP
#define SOUND_HPP
#include <ParticuleApi/System/Resource.hpp>
#include <string>

namespace Particule::Api
{
    class Sound
    {
    public:
        Sound();
        Sound(Resource path);
        Sound(const Sound& other);
        Sound& operator=(const Sound& other);
        ~Sound();

        void Play();
        void Pause();
        void Stop();
        void SetVolume(float volume);
        void SetPitch(float pitch);
        void SetLoop(bool loop);
        void SetPosition(float position);
        void SetPlayingOffset(float time);
        
        float GetVolume();
        float GetPitch();
        bool GetLoop();
        float GetPosition();
        float GetPlayingOffset();
        float GetDuration();

        bool IsPlaying();
        bool IsPaused();
        bool IsStopped();
        bool IsLooping();
    };
}
#endif // SOUND_HPP