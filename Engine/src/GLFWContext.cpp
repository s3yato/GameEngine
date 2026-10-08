#include <atlas/GLFWContext.hpp>
#include <stdexcept>

atlas::GLFWContext::GLFWContext()
{
    if (!glfwInit()) {
        throw std::runtime_error("ОШибка при инициализации GLFW\n");
    }
}

atlas::GLFWContext::~GLFWContext()
{
    glfwTerminate();
}