#pragma once

#include <atlas/math/Transform.hpp>
#include <string>

namespace atlas 
{
    class GameObject
    {
        public:
            GameObject(const std::string& name): m_name(name), m_transform( Vec2(0, 0), Vec2(1, 1), 0.0f ) {}
            Transform& transform() {
                return m_transform;
            }
            const Transform& transform() const {
                return m_transform;
            }
            private:
                Transform m_transform;
                std::string m_name;
    };
}