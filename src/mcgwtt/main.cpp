// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "WindowController.h"

#include "GameWorld.h"
#include "Player.h"
#include "Platform.h"
#include "DebugGrid.h"

#include "CameraController.h"
#include "ViewController.h"

#include "window/GameWindow.h"

int main() {
    sf::ContextSettings winContextSettings(0, 0, 16);
    sf::RenderWindow win(
            sf::VideoMode::getFullscreenModes()[0],
            "MegaClockGameWithTimeTravelling 0.0.1 from ATFProject Game studio!",
            sf::Style::Default,
            winContextSettings);

    window::GameWindow window(&win);

    sf::Image icon;
    icon = engine::resourceHandler.addRes(new engine::Texture("icon.png"))->getTex()->copyToImage();
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    win.setPosition(sf::Vector2i(550, 50));
    win.setFramerateLimit(165);
    win.setActive(true);

    window.addGameObject(new mcgwtt::WindowController(&window), nullptr, nullptr);

    auto world = new mcgwtt::GameWorldPhysics(b2Vec2(0, 9.8), 1 / 165.f, 8, 3);

    window.addGameObject(nullptr, world, nullptr);
    window.addGameObject(nullptr, nullptr, new mcgwtt::CameraController(&win, 30));
    window.addGameObject(nullptr, nullptr, new mcgwtt::ViewController());

    window.addGameObject(nullptr, new mcgwtt::PlayerPhysics(world, 0, 0),
                         new mcgwtt::PlayerGraphics(&win));

    window.addGameObject(nullptr,
                         new mcgwtt::PlatformPhysics(world, 0, 6, 4, 1),
                         new mcgwtt::PlatformGraphics(&win));

    window.addGameObject(nullptr, nullptr, new mcgwtt::DebugGridGraphics(&win));

    window.startRendering();

    return 0;
}
