//
// Created by livefish on 1/08/24.
//

#include "GameWindow.h"

#include "components/WindowControl/WindowController.h"
#include "components/Demo components/WindowMovementController.h"


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

    window.addGameObject(new mcgwtt::components::WindowController(&window), nullptr, nullptr);
    window.addGameObject(new mcgwtt::components::WindowMovementController(&window), nullptr, nullptr);

    window.startRendering();
    return 0;
}
