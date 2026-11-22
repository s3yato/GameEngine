
#include <atlas/input/Input.hpp>
#include <atlas/Window.hpp>

namespace atlas
{
    Input::Input(const Window& window)
        : m_window(window)
    {
    }

    bool Input::isKeyPressed(int key) const
    {
        return m_window.isKeyPressed(key);
    }
}
