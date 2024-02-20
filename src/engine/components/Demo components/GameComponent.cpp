//
// Created by livefish on 2/20/24.
//

#include "GameComponent.h"
#include "game/Game.h"

namespace engine::components {
    GameComponent::GameComponent(window::GameWindow *win) {
        this->addObserver(win);
    }

    void GameComponent::tick(game::GameObject *gameObject, game::Game &game) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            notify(std::shared_ptr<events::Event>(
                    new events::WindowMoveEvent(10, 0)
            ));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            notify(std::shared_ptr<events::Event>(
                    new events::WindowMoveEvent(-10, 0)
            ));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            notify(std::shared_ptr<engine::events::Event>(
                    new events::WindowMoveEvent(0, -10)
            ));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            notify(std::shared_ptr<events::Event>(
                    new events::WindowMoveEvent(0, 10)
            ));
        }
    }
}

