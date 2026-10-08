#include <atlas/Window.hpp>

atlas::Window::Window()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(1920, 1080, "Engine", NULL, NULL);
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