
#pragma once

namespace atlas
{
    class Window;

    class Input
    {
    public:
        explicit Input(const Window& window);

        bool isKeyPressed(int key) const;

    private:
        const Window& m_window;
    };
}
