#include <atlas/math/Transform.hpp>

namespace atlas {
    Vec2& Transform::position() {
        return m_position;
    } 

    const Vec2& Transform::position() const {
        return m_position;
    }

    Vec2& Transform::scale() {
        return m_scale;
    }

    const Vec2& Transform::scale() const {
        return m_scale;
    }

    float& Transform::rotation() {
        return m_rotation;
    }

    float Transform::rotation() const {
        return m_rotation;
    }

    Matrix4 Transform::matrix() const
    {
        Matrix4 translation = Matrix4::translation(
            m_position.x(),
            m_position.y(),
            0.0f
        );

        Matrix4 rotation = Matrix4::rotationZ(m_rotation);

        Matrix4 scale = Matrix4::scale(
            m_scale.x(),
            m_scale.y(),
            1.0f
        );

        return translation * rotation * scale;
    }
}