// Copyright (c) 2024. ATF project organization!

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "GameWindow.h"

#include "game/Timer.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _isActive(false), _win(window) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
        _game.addObserver(this);
    }

    engine::game::GameProperties GameWindow::getProperties() const {
        return _gameProperties;
    }

    void GameWindow::setProperties(const engine::game::GameProperties &newProps) {
        _gameProperties = newProps;
    }

    void GameWindow::startRendering() {
        _isActive = true;
        std::cout << "Started!" << std::endl;

        // Fix for windows: explicit game resize on program start
        // Without this line the game will have (0, 0) size
        // Works perfectly on Linux without it :(
        notify(window::WindowResizeEvent(_win->getSize().x, _win->getSize().y));

        engine::ActionPerSecond tick(_gameProperties.targetTps, 1, [this]() {
            if (_isActive) {
                _game.tick();
            }
        });

        engine::ActionPerSecond drawFrame(_gameProperties.maxFps, 1, [this]() {
            _win->clear(sf::Color(64, 64, 64));
            _game.draw();
            _win->display();
        });

        engine::ActionPerSecond output(2, 0, [&tick, &drawFrame]() {
            std::cout << "TPS: " << tick.getActualActionRate() << "; FPS: " << drawFrame.getActualActionRate()
                      << std::endl;
        });


        while (_win->isOpen()) {
            handleSfmlEvents();

            tick.tryAction();
            drawFrame.tryAction();
            output.tryAction();
        }
    }

    void GameWindow::handleSfmlEvents() {
        sf::Event event{};

        while (_win->pollEvent(event)) {
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

    void GameWindow::addGameObject(engine::components::InputComponent *ic,
                                                        engine::components::PhysicsComponent *pc,
                                                        engine::components::GraphicsComponent *gc) {
        _game.addGameObject(std::make_unique<engine::game::GameObject>(ic, pc, gc));
    }

    void GameWindow::onNotify(const engine::Event &event) {
        ENGINE_CHECK_EVENT(WindowCloseEvent,
                           _win->close();
        )
        ENGINE_CHECK_EVENT(WindowViewChangedEvent,
                           _win->setView(e->newView);
        )
    }
}
