#include <atlas/Time.hpp>

atlas::Time::Time()
{
    m_lastTime = std::chrono::steady_clock::now();
}

void atlas::Time::update()
{
    auto now = std::chrono::steady_clock::now();

    auto delta = now - m_lastTime;

    m_lastTime = now;

    m_deltaTime =
        std::chrono::duration<float>(delta).count();
}

float atlas::Time::deltaTime() const
{
    return m_deltaTime;
}