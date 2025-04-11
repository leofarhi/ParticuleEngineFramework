#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>

namespace Particule::Api
{
    class Time
    {
    private:
        std::clock_t m_startTime;
        std::clock_t m_lastTime;
        double m_deltaTime; // en secondes

    public:
        Time();
        Time(const Time& other);
        Time& operator=(const Time& other);
        ~Time();

        void Update();

        double DeltaTime() const;        // en secondes
        double TimeSinceStart() const;   // en secondes

        static void Delay(double time);  // en secondes
        static void DelayMs(int ms);     // en millisecondes
    };
}

#endif // TIME_HPP