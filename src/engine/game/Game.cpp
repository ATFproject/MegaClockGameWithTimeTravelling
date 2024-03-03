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
        _size = size;
    }

    void Game::onNotify(const events::Event &event) {
        ENGINE_CHECK_EVENT(window::WindowResizeEvent,
                           resize(e->newSize);
        )
    }

    Game::~Game() {
        for (auto &_gameObject : _gameObjects) {
            delete _gameObject;
        }
    }

    sf::Vector2u Game::getSize() const {
        return _size;
    }
}