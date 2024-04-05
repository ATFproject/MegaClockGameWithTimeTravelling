//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "WindowControl/WindowController.h"
#include "TGUI test/MenuScreen.h"

#include "game/GameWorld.h"
#include "game/Player.h"

int main() {
    // set antialiasing level to 16
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

    window.addGameObject(new mcgwtt::components::WindowController(&window, &win), nullptr, nullptr);

    auto world = new mcgwtt::components::game::GameWorldPhysics(
            window, b2Vec2(0, 0.25), 1 / 165.f, 8, 3);

    window.addGameObject(nullptr, world, nullptr);

    window.addGameObject(nullptr, new mcgwtt::components::game::PlayerPhysics(world, 50, 100),
                         new mcgwtt::components::game::PlayerGraphics(&win));


    window.startRendering();

    return 0;
}
