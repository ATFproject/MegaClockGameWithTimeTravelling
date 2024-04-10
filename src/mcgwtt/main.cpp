//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "WindowController.h"

#include "GameWorld.h"
#include "Player.h"
#include "CameraController.h"

int main() {
    sf::ContextSettings winContextSettings(0, 0, 16);
    sf::RenderWindow win(
            sf::VideoMode::getFullscreenModes()[0],
            "MegaClockGameWithTimeTravelling 0.0.1 from ATFProject Game studio!",
            sf::Style::Default,
            winContextSettings);

    window::GameWindow window(&win);

    sf::Image icon;
    icon = engine::resourceHandler.addRes(new engine::Texture("icon.png"))->getTex().copyToImage();
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    win.setPosition(sf::Vector2i(550, 50));
    win.setFramerateLimit(165);
    win.setActive(true);

    window.addGameObject(new mcgwtt::WindowController(&window), nullptr, nullptr);

    auto world = new mcgwtt::GameWorldPhysics(
            window, b2Vec2(0, 0.25), 1 / 165.f, 8, 3);

    window.addGameObject(nullptr, world, nullptr);
    window.addGameObject(nullptr, nullptr, new mcgwtt::CameraController(&win, 30));

    window.addGameObject(nullptr, new mcgwtt::PlayerPhysics(world, 0, 0),
                         new mcgwtt::PlayerGraphics(&win));

    window.startRendering();

    return 0;
}
