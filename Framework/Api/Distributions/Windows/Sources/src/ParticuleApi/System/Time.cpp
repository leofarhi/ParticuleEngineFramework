#include <ParticuleApi/System/Time.hpp>

namespace Particule::Api
{

    Time::Time()
    {
        m_startTime = std::clock();
        m_lastTime = m_startTime;
        m_deltaTime = 0;
    }

    Time::Time(const Time& other)
        : m_startTime(other.m_startTime),
        m_lastTime(other.m_lastTime),
        m_deltaTime(other.m_deltaTime)
    {}

    Time& Time::operator=(const Time& other)
    {
        if (this != &other) {
            m_startTime = other.m_startTime;
            m_lastTime = other.m_lastTime;
            m_deltaTime = other.m_deltaTime;
        }
        return *this;
    }

    Time::~Time()
    {}

    void Time::Update()
    {
        std::clock_t now = std::clock();
        m_deltaTime = static_cast<double>(now - m_lastTime) / CLOCKS_PER_SEC;
        m_lastTime = now;
    }

    double Time::DeltaTime() const
    {
        return m_deltaTime;
    }

    double Time::TimeSinceStart() const
    {
        return static_cast<double>(std::clock() - m_startTime) / CLOCKS_PER_SEC;
    }

    void Time::Delay(double time)
    {
        std::clock_t end = std::clock() + static_cast<std::clock_t>(time * CLOCKS_PER_SEC);
        while (std::clock() < end) {
            // busy-wait
        }
    }

    void Time::DelayMs(int ms)
    {
        Delay(ms / 1000.0);
    }

}