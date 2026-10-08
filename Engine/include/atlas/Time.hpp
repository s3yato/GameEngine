#pragma once

#include <chrono>

namespace atlas
{
    class Time
    {
    public:
        Time();

        void update();
        float deltaTime() const;

    private:
        std::chrono::steady_clock::time_point m_lastTime;
        float m_deltaTime = 0.0f;
    };
}