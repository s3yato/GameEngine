
#pragma once

namespace atlas
{
    class Input;

    class IGame
    {
    public:
        virtual ~IGame() = default;

        virtual void initialize() = 0;

        virtual void update(float dt, const Input& input) = 0;
        virtual void render() = 0;

        virtual void shutdown() = 0;
    };
}
