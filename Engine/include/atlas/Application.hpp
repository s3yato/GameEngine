#pragma once

#include <atlas/GLFWContext.hpp>
#include <atlas/Window.hpp>
#include <atlas/Time.hpp>
#include <atlas/math/Vec2.hpp>
#include <atlas/scene/GameObject.hpp>
#include <atlas/render/Render.hpp>
#include <atlas/IGame.hpp>
#include <atlas/input/input.hpp>

#include <memory>


#pragma once

#include <atlas/GLFWContext.hpp>
#include <atlas/Window.hpp>
#include <atlas/Time.hpp>
#include <atlas/input/Input.hpp>
#include <atlas/IGame.hpp>

namespace atlas
{
    class Application
    {
    public:
        explicit Application(IGame& game);
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        void run();
        void setResizeCallback(std::function<void(int, int)> callback);
    private:
        GLFWContext m_glfw;
        Window m_window;
        Input m_input;
        Time m_time;
        IGame& m_game;
    };
}
