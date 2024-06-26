// Copyright (c) 2024. ATF project organization!

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GameWindow.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _isActive(false), _win(window), _gui(*window) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
        _game.addObserver(this);
    }

    void GameWindow::startRendering() {
        _isActive = true;
        std::cout << "Started!" << std::endl;

        // Fix for windows: explicit game resize on program start
        // Without this line the game will have (0, 0) size
        // Works perfectly on LInux without it :(
        notify(window::WindowResizeEvent(_win->getSize().x, _win->getSize().y));

        while (_win->isOpen()) {
            _win->clear(sf::Color(64, 64, 64));
            handleSfmlEvents();

            if (_isActive) {
                _game.tick();
            }
            _game.draw();
            _gui.draw();

            _win->display();
        }
    }

    void GameWindow::handleSfmlEvents() {
        sf::Event event{};

        while (_win->pollEvent(event)) {
            _gui.handleEvent(event);

            switch (event.type) {
                case sf::Event::Closed:
                    _win->close();
                    break;

                case sf::Event::LostFocus:
                    _isActive = false;
                    notify(WindowFocusChangeEvent{false});
                    break;

                case sf::Event::GainedFocus:
                    _isActive = true;
                    notify(WindowFocusChangeEvent{true});
                    break;

                case sf::Event::Resized:
                    notify(WindowResizeEvent(event.size.width, event.size.height));
                    break;

                case sf::Event::KeyPressed:
                    notify(KeyPressedEvent(event.key));
                    break;

                case sf::Event::KeyReleased:
                    notify(KeyReleasedEvent(event.key));
                    break;

                default:
                    break;
            }
        }
    }

    engine::game::GameObject *GameWindow::addGameObject(engine::components::InputComponent *ic,
                                                        engine::components::PhysicsComponent *pc,
                                                        engine::components::GraphicsComponent *gc) {
        auto gameObject = new engine::game::GameObject(ic, pc, gc);
        _game.addGameObject(gameObject);
        return gameObject;
    }

    void GameWindow::removeGameObject(engine::game::GameObject *obj) {
        _game.removeGameObject(obj);
    }

    void GameWindow::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(WindowCloseEvent,
                           _win->close();
        )
        ENGINE_CHECK_EVENT(WindowViewChangedEvent,
                           _win->setView(e->_newView);
        )
    }

    tgui::Gui &GameWindow::getGui() {
        return _gui;
    }
}
