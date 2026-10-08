#pragma once

#include <atlas/Math/Vec2.hpp>

namespace atlas 
{
    class Transform 
    {
        public:
            Transform(
                const atlas::Vec2& position,
                const atlas::Vec2& scale, 
                float rotation
            ): m_position(position), m_scale(scale), m_rotation(rotation) {}

            Vec2& position();
            const Vec2& position() const;

            Vec2& scale();
            const Vec2& scale() const;

            float& rotation();
            float rotation() const;
        private:
            Vec2 m_position;
            Vec2 m_scale;
            float m_rotation;
    };
}