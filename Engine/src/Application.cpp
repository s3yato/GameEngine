
#include <atlas/Application.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace atlas
{
    Application::Application(IGame& game)
        : m_input(m_window),
        m_game(game)
    {
        if (!gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        m_game.initialize();
    }

    Application::~Application()
    {
        m_game.shutdown();
    }

    void Application::run()
    {
        while (!m_window.shouldClose())
        {
            m_window.pollEvents();

            m_time.update();
            const float dt = m_time.deltaTime();

            m_game.update(dt, m_input);
            m_game.render();

            m_window.swapBuffers();
        }
    }

    void Application::setResizeCallback(
        std::function<void(int, int)> callback
    )
    {
        m_window.setResizeCallback(std::move(callback));
    }
}