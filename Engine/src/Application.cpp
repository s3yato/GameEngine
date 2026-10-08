#include <atlas/Application.hpp>
#include <iostream>

atlas::Application::Application(): m_player("Player") { }

atlas::Application::~Application() {

}

void atlas::Application::render() 
{
    m_render.clear();
    m_render.render();
}

void atlas::Application::run() {
    while (!m_window.shouldClose()) {
        m_window.pollEvents();

        m_time.update();

        float dt = m_time.deltaTime();
        update(dt);
        render();
        m_window.swapBuffers();
    }
}

void atlas::Application::update(float dt) {
    constexpr float speed = 200.0f;

    Vec2 direction;
    if (m_window.isKeyPressed(GLFW_KEY_W)) 
        direction.y() += 1.0f;
    
    if (m_window.isKeyPressed(GLFW_KEY_S)) 
        direction.y() -= 1.0f;
    
    if (m_window.isKeyPressed(GLFW_KEY_A)) 
        direction.x() -= 1.0f;
    
    if (m_window.isKeyPressed(GLFW_KEY_D)) 
        direction.x() += 1.0f;

    if (direction.length() > 0.0f) 
        direction = direction.normalized();

    m_player.transform().position() += direction * speed * dt;
}