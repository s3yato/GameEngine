
#include "Game.hpp"

#include <atlas/input/Input.hpp>
#include <atlas/math/Vec2.hpp>

#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
Game::~Game() = default;

void Game::initialize()
{
    m_playerTexture =
        std::make_unique<atlas::Texture>("assets/player.png");

    m_playerSprite =
        std::make_unique<atlas::SpriteRender>(*m_playerTexture);

    m_markerTexture =
        std::make_unique<atlas::Texture>("assets/enemy.png");
    m_markerSprite =
        std::make_unique<atlas::SpriteRender>(*m_markerTexture);

    m_render = std::make_unique<atlas::Render>();
    m_player.transform().scale() = { 0.5f, 0.5f };
    m_marker.transform().scale() = { 0.5f, 0.5f };
}

void Game::update(float dt, const atlas::Input& input)
{
    constexpr float speed = 0.5f;

    atlas::Vec2 direction;

    if (input.isKeyPressed(GLFW_KEY_W))
        direction.y() += 1.0f;

    if (input.isKeyPressed(GLFW_KEY_S))
        direction.y() -= 1.0f;

    if (input.isKeyPressed(GLFW_KEY_A))
        direction.x() -= 1.0f;

    if (input.isKeyPressed(GLFW_KEY_D))
        direction.x() += 1.0f;

    if (direction.length() > 0.0f)
        direction = direction.normalized();

    m_player.transform().position() += direction * speed * dt;
    m_camera.position() = m_player.transform().position();
}

void Game::render()
{
    m_render->clear();

    const auto view = m_camera.viewMatrix();
    const auto projection = m_camera.projectionMatrix();

    m_playerSprite->render(
        m_player.transform().matrix(),
        view,
        projection
    );

    m_markerSprite->render(
        m_marker.transform().matrix(),
        view,
        projection
    );
}

void Game::shutdown()
{
    m_playerSprite.reset();
    m_markerSprite.reset();

    m_playerTexture.reset();
    m_markerTexture.reset();

    m_render.reset();
}

void Game::onResize(int width, int height)
{
    m_camera.setViewportSize(
        static_cast<float>(width),
        static_cast<float>(height)
    );
}
