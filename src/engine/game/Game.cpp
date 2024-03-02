//
// Created by livefish on 2/20/24.
//

#include "Game.h"
#include "GameObject.h"
#include "GameWindow.h"

namespace engine::game {
    void Game::operator<<(GameObject *toAdd) {
        _gameObjects.push_back(toAdd);
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
        std::cout << "Game received event: " + to_string(event->type) << std::endl;

        switch (event->type) {
            case events::Type::WINDOW_RESIZED: {
                auto *resizeEvent = dynamic_cast<window::WindowResizeEvent *>(event);
                resize(resizeEvent->newSize);
                break;
            }
            default:
                break;
        }
    }

    Game::~Game() {
        for (auto & _gameObject : _gameObjects) {
            delete _gameObject;
        }
    }
}