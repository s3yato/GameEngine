#pragma once

#include <atlas/GLFWContext.hpp>
#include <atlas/Window.hpp>
#include <atlas/Time.hpp>
#include <atlas/Math/Vec2.hpp>
#include <atlas/scene/GameObject.hpp>
#include <atlas/render/Render.hpp>

namespace atlas 
{
    class Application 
    {
        public:
            Application();
            ~Application();

            void run();
            void update(float dt);
            void render();
        private:
            GLFWContext m_glfw;
            Window m_window;
            Time m_time;
            GameObject m_player;
            Render m_render;
    };
}