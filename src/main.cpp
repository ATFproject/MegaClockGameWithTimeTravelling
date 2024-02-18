/* NASRAT */

#include "game/game.h"

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
    win.setActive(true);

    while (win.isOpen()) {
        sf::Event event{};
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                win.close();
            }
        }

        win.clear();
        win.display();
    }

    return 0;
}
