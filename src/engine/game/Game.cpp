//
// Created by livefish on 2/20/24.
//

#include "Game.h"
#include "GameObject.h"

namespace engine::game {
    void Game::operator<<(GameObject *toAdd) {
        _gameObjects.push_back(toAdd);
        auto tex = resources::load<sf::Texture>("icon.png");
    }

    void Game::tick() {
        sf::Time elapsed = _timer.getElapsedTime();
        for (GameObject *gameObject : _gameObjects) {
            gameObject->tick(elapsed, *this);
        }

        for (GameObject *gameObject : _gameObjects) {
            gameObject->draw();
        }
        _timer.restart();
    }

    void Game::resize(sf::Vector2u size) {
        std::cout << "Test engine size output! " << size.x << ", " << size.y << std::endl;
        // TODO: Convert this to graphics component and use it
    }

    void Game::onNotify(events::Event *event) {
        std::cout << "Game received event: " + events::getTypeString(event->type) << std::endl;

        switch (event->type) {
            case events::Type::WINDOW_RESIZED: {
                auto *resizeEvent = dynamic_cast<events::WindowResizeEvent *>(event);
                resize(resizeEvent->newSize);
                break;
            }
            default:
                break;
        }
    }
}