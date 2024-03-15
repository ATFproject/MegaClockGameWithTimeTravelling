//
// Created by livefish on 2/20/24.
//

#include "Game.h"
#include "GameObject.h"
#include "GameWindow.h"

namespace engine::game {
    void Game::operator<<(GameObject *toAdd) {
        _gameObjects.push_back(toAdd);
        addObserver(toAdd);
        toAdd->init(*this);
    }

    void Game::removeGameObject(GameObject *toRemove) {
        _gameObjectsToDelete.push_back(toRemove);
    }

    void Game::tick() {
        for (GameObject *gameObject : _gameObjects) {
            gameObject->tick(*this);
        }

        for (auto &toDelete : _gameObjectsToDelete) {
            _gameObjects.erase(std::find(_gameObjects.begin(), _gameObjects.end(), toDelete));
            removeObserver(toDelete);
            delete toDelete;
        }
        _gameObjectsToDelete.clear();
    }

    void Game::draw() {
        for (GameObject *gameObject : _gameObjects) {
            gameObject->preDraw();
        }
        for (GameObject *gameObject : _gameObjects) {
            gameObject->draw();
        }
        for (GameObject *gameObject : _gameObjects) {
            gameObject->postDraw();
        }
    }

    void Game::onNotify(const events::Event &event) {
        ENGINE_CHECK_EVENT(window::WindowResizeEvent,
                           notify(GameResizeEvent(e->newSize));
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