#pragma once

#include <GLFW/glfw3.h>

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
        private:
            GLFWwindow* m_window;
    };
}