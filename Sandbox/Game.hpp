
#pragma once

#include <atlas/IGame.hpp>
#include <atlas/scene/GameObject.hpp>
#include <atlas/render/Render.hpp>
#include <atlas/render/Camera2D.hpp>
#include <atlas/graphics/Texture.hpp>
#include <atlas/graphics/SpriteBatch.hpp>

#include <memory>

class Game final : public atlas::IGame
{
public:
    Game() = default;
    ~Game() override;

    void initialize() override;
    void update(float dt, const atlas::Input& input) override;
    void render() override;
    void shutdown() override;
    void onResize(int width, int height);

private:
    atlas::GameObject m_player{ "Player" };
	atlas::GameObject m_marker{ "World Marker" };
    atlas::GameObject m_playerCopy{ "PlayerCopy" };
    
    std::unique_ptr<atlas::SpriteBatch> m_playerBatch;
    std::unique_ptr<atlas::SpriteBatch> m_markerBatch;

    std::unique_ptr<atlas::Texture> m_playerTexture;
    std::unique_ptr<atlas::Texture> m_markerTexture;

    std::unique_ptr<atlas::Render> m_render;

    atlas::RenderStats m_renderStats;
    atlas::Camera2D m_camera{ 1920.0f, 1080.0f };
};  
