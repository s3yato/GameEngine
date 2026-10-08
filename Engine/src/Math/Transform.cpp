#include <atlas/Math/Transform.hpp>

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
}