//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "components/WindowControl/WindowController.h"
#include "components/Box2d Test/World.h"
#include "mcgwtt/components/Box2d Test/Spinning box.h"

int main() {
    // set antialiasing level to 16
    sf::ContextSettings winContextSettings(0, 0, 16);
    sf::RenderWindow win(
            sf::VideoMode(1200, 900),
            "MegaClockGameWithTimeTravelling 0.0.1 from ATFProject Game studio!",
            sf::Style::Default,
            winContextSettings);
    win.setFramerateLimit(165);
    win.setActive(true);

    sf::Image icon;
    win.setPosition(sf::Vector2i(550, 50));
    icon.loadFromFile("../resources/images/icon.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window::GameWindow window(&win);
    window.addGameObject(new mcgwtt::components::WindowController(&window, &win), nullptr, nullptr);

    auto worldPhysics = new mcgwtt::components::WorldPhysics(
            window, b2Vec2(0, 9.8), 1 / 165.f, 8, 3);
    window.addGameObject(nullptr, worldPhysics, nullptr);
    window.addGameObject(
            nullptr,
            new mcgwtt::components::BoxPhysics(worldPhysics, 1000, 600, 400),
            new mcgwtt::components::BoxGraphics(
                    &win, sf::Color(99, 34, 112, 128)));


    window.startRendering();

    return 0;
}
