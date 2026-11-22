
#include <atlas/Application.hpp>

#include "Game.hpp"

int main()
{
    Game game;
    atlas::Application app(game);

    app.setResizeCallback(
        [&game](int width, int height)
        {
            game.onResize(width, height);
        }
    );

    app.run();

    return 0;
}
