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
        for (int i = 0; i < 256; ++i) {
            _click[i] = _keys[i] && !_keysOld[i];
        }
        memcpy(_keysOld, _keys, 256);

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
            gameObject->draw();
        }
    }

    void Game::onNotify(const events::Event &event) {
        ENGINE_CHECK_EVENT(window::WindowResizeEvent,
                           notify(GameResizeEvent(e->_newSize));
        )
        ENGINE_CHECK_EVENT(window::KeyPressedEvent,
                           _keys[e->_keyEvent.scancode] = true;
        )
        ENGINE_CHECK_EVENT(window::KeyReleasedEvent,
                           _keys[e->_keyEvent.scancode] = false;
        )
        ENGINE_CHECK_EVENT(window::WindowFocusChangeEvent,
                           if (!e->_inFocus) {
                               memset(_keys, 0, 256);
                               memset(_keysOld, 0, 256);
                               memset(_click, 0, 256);
                           }
        )
    }

    Game::~Game() {
        for (auto &gameObject : _gameObjects) {
            delete gameObject;
        }
    }

    sf::Vector2u Game::getSize() const {
        return _size;
    }

    bool Game::isKeyPressed(const sf::Keyboard::Scancode &k) {
        return _keys[k];
    }

    bool Game::wasKeyClicked(const sf::Keyboard::Scancode &k) {
        return _click[k];
    }
}