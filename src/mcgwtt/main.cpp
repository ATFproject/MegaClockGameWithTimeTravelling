//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "components/WindowControl/WindowController.h"

#include "components/Pong/Paddle.h"

int main() {
    // set antialiasing level to 16
    sf::ContextSettings winContextSettings(0, 0, 16);
    sf::RenderWindow win(
            sf::VideoMode(800, 600),
            "MegaClockGameWithTimeTravelling 0.0.1 from ATFProject Game studio!",
            sf::Style::Default,
            winContextSettings);
    win.setVerticalSyncEnabled(false);
    win.setActive(true);

    sf::Image icon;
    icon.loadFromFile("../resources/images/icon.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window::GameWindow window(&win);
    sf::String myString("Hello World");
    window.addGameObject(new mcgwtt::components::WindowController(&window), nullptr, nullptr);

    window.addGameObject(nullptr, new mcgwtt::components::PaddlePhysics(100, 200),
                         new mcgwtt::components::PaddleGraphics(&win, sf::Color::Red));

    window.addGameObject(nullptr, new mcgwtt::components::PaddlePhysics(700, 200),
                         new mcgwtt::components::PaddleGraphics(&win, sf::Color::Blue));

    window.startRendering();
    return 0;
}
