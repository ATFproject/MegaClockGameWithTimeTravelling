//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "components/WindowControl/WindowController.h"

#include "components/Box2d Test/Memtest.h"

#include "components/TGUI test/MenuScreen.h"

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

    auto uiController = new mcgwtt::components::UIController(&window, &win);
    window.addGameObject(uiController, nullptr, nullptr);

    window.addGameObject(nullptr, nullptr, new mcgwtt::components::MenuScreenGraphics(&window, uiController));
    window.startRendering();

    return 0;
}
