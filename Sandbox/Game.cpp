
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

    m_markerTexture =
        std::make_unique<atlas::Texture>("assets/enemy.png");

    m_playerBatch =
        std::make_unique<atlas::SpriteBatch>(*m_playerTexture);

    m_markerBatch =
        std::make_unique<atlas::SpriteBatch>(*m_markerTexture);

    m_playerBatch->setStats(&m_renderStats);
    m_markerBatch->setStats(&m_renderStats);

    m_render = std::make_unique<atlas::Render>();

    m_player.transform().scale() = { 0.5f, 0.5f };
    m_marker.transform().scale() = { 0.5f, 0.5f };

    m_playerCopy.transform().position() = { 1.5f, 0.0f };
    m_playerCopy.transform().scale() = { 0.5f, 0.5f };
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
    m_renderStats.reset();

    const auto view = m_camera.viewMatrix();
    const auto projection = m_camera.projectionMatrix();
    const atlas::TextureRegion fullTexture{};

    m_playerBatch->begin(view, projection);
    m_playerBatch->submit(m_player.transform().matrix(), fullTexture);
    m_playerBatch->submit(m_playerCopy.transform().matrix(), fullTexture);
    m_playerBatch->flush();

    m_markerBatch->begin(view, projection);
    m_markerBatch->submit(m_marker.transform().matrix(), fullTexture);
    m_markerBatch->flush();
}

void Game::shutdown()
{
    m_playerBatch.reset();
    m_markerBatch.reset();

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
