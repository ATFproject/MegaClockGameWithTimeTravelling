// Copyright (c) 2024. ATF project organization!

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Game.h"
#include "GameObject.h"
#include "window/GameWindow.h"

namespace engine::game {
    Game::Game() : _resourceHandler(std::make_unique<ResourceHandler>()) {
        resourceHandler = _resourceHandler.get();
    }

    void Game::addGameObject(std::unique_ptr<GameObject> toAdd) {
        addObserver(toAdd.get());
        toAdd->init(*this);
        _gameObjects.push_back(std::move(toAdd));
    }

    void Game::tick() {
        const int keyboardKeyCount = 256;
        for (int i = 0; i < keyboardKeyCount; ++i) {
            _click[i] = _keys[i] && !_keysOld[i];
        }
        memcpy(_keysOld, _keys, keyboardKeyCount);

        for (auto &gameObject : _gameObjects) {
            gameObject->tick(*this);
        }
    }

    void Game::draw() {
        for (auto &gameObject : _gameObjects) {
            gameObject->draw();
        }
    }

    void Game::onNotify(const Event &event) {
        ENGINE_CHECK_EVENT(window::WindowViewChangedEvent, notify(*e);)

        ENGINE_CHECK_EVENT(window::WindowResizeEvent,
                           notify(GameResizeEvent(e->newSize));
        )
        ENGINE_CHECK_EVENT(window::KeyPressedEvent,
                           _keys[e->keyEvent.scancode] = true;
        )
        ENGINE_CHECK_EVENT(window::KeyReleasedEvent,
                           _keys[e->keyEvent.scancode] = false;
        )
        ENGINE_CHECK_EVENT(window::WindowFocusChangeEvent,
                           if (!e->inFocus) {
                               memset(_keys, 0, 256);
                               memset(_keysOld, 0, 256);
                               memset(_click, 0, 256);
                           }
        )
    }

    sf::Vector2u Game::getSize() const {
        return _size;
    }

    bool Game::isKeyPressed(const sf::Keyboard::Scancode k) {
        return _keys[k];
    }

    bool Game::wasKeyClicked(const sf::Keyboard::Scancode k) {
        return _click[k];
    }
}
