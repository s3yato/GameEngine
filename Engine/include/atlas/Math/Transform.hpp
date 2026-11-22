#pragma once

#include <atlas/Math/Vec2.hpp>
#include <atlas/Math/Matrix4.hpp>

namespace atlas 
{
    class Transform 
    {
        public:
            Transform() = default;

            Transform(
                const Vec2& position,
                const Vec2& scale, 
                float rotation
            ): m_position(position), m_scale(scale), m_rotation(rotation) {}

            Vec2& position();
            const Vec2& position() const;

            Vec2& scale();
            const Vec2& scale() const;

            float& rotation();
            float rotation() const;
 
            Matrix4 matrix() const;
        private:
            Vec2 m_position{ 0.0f, 0.0f };
            Vec2 m_scale{ 1.0f, 1.0f };
            float m_rotation = 0.0f;
    };
}