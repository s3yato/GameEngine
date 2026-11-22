#include <atlas/Window.hpp>
#include <stdexcept>
#include <utility>

atlas::Window::Window()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(
        1920, 1080, "Engine", nullptr, nullptr
    );

    if (!m_window)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
}


atlas::Window::~Window()
{
    glfwDestroyWindow(m_window);
}

bool atlas::Window::shouldClose()  
{
    return glfwWindowShouldClose(m_window);
}

void atlas::Window::pollEvents()
{
    glfwPollEvents();
}

bool atlas::Window::isKeyPressed(int key) const 
{
    if (glfwGetKey(m_window, key) == GLFW_PRESS) {
        return true;
    }
    return false;
}

void atlas::Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void atlas::Window::setResizeCallback(
    std::function<void(int, int)> callback
)
{
    m_resizeCallback = std::move(callback);

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(
        m_window,
        framebufferSizeCallback
    );
}

void atlas::Window::framebufferSizeCallback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(0, 0, width, height);

    auto* self = static_cast<Window*>(
        glfwGetWindowUserPointer(window)
        );

    if (self && self->m_resizeCallback)
        self->m_resizeCallback(width, height);
}