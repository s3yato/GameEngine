#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

namespace atlas
{
    class Window
    {
    public:
        Window();
        ~Window();

        bool shouldClose();
        void pollEvents();
        bool isKeyPressed(int key) const;
        void swapBuffers();
        void setResizeCallback(std::function<void(int, int)> callback);
    private:
        GLFWwindow* m_window;
        std::function<void(int, int)> m_resizeCallback;
        static void framebufferSizeCallback(
            GLFWwindow* window,
            int width,
            int height
        );
    };
}