//
// Created by livefish on 2/19/24.
//

#include "GameWindow.h"
#include "game/GameObject.h"
#include "Events.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _win(window), _isActive(false) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
    }

    void GameWindow::startRendering() {
        _isActive = true;
        std::cout << "Started!" << std::endl;

        while (_win->isOpen()) {
            _win->clear();
            _handleSfmlEvents();

            if (_isActive) {
                _game.tick();
            }
            _win->display();
        }
    }

    void GameWindow::_handleSfmlEvents() {
        sf::Event event{};

        while (_win->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    _win->close();
                    break;

                case sf::Event::LostFocus:
                    _isActive = false;
                    std::cout << "Lost focus" << std::endl;
                    notify(WindowFocusChangeEvent{false});
                    break;

                case sf::Event::GainedFocus:
                    _isActive = true;
                    std::cout << "Gained focus" << std::endl;
                    notify(WindowFocusChangeEvent{true});
                    break;

                case sf::Event::Resized:
                    notify(WindowResizeEvent(event.size.width, event.size.height));
                    break;

                default:
                    break;
            }
        }
    }

    void GameWindow::addGameObject(engine::components::InputComponent *ic,
                                   engine::components::PhysicsComponent *pc,
                                   engine::components::GraphicsComponent *gc) {
        _game << new engine::game::GameObject(ic, pc, gc);
    }

    void GameWindow::onNotify(const engine::events::Event &event) {
        ENGINE_CHECK_EVENT(WindowCloseEvent,
                           _win->close();
        )
        ENGINE_CHECK_EVENT(WindowMoveEvent,
                           _win->setPosition(_win->getPosition() + e->move);
        )
    }

    void GameWindow::addWorld(b2World *world) {
        _game._world = world;
    }
}
