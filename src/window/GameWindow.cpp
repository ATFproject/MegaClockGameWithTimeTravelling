//
// Created by livefish on 2/19/24.
//

#include "GameWindow.h"
#include "game/GameObject.h"
#include "components/Demo components/GameComponent.h"
#include "observers/GameEvents.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _win(window), _isActive(false) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
        auto *window_control = new engine::game::GameObject();
        window_control->setInput(new engine::components::GameComponent(this));

        _game << window_control;
    }

    void GameWindow::startRendering() {
        _isActive = true;
        while (_win->isOpen()) {
            _handleSfmlEvents();

            if (_isActive) {
                _game.tick();
            }

            _win->display();
        }
    }

    void GameWindow::_handleSfmlEvents() {
        sf::Event event{};

        using namespace engine::events;

        while (_win->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    _win->close();
                    break;

                case sf::Event::LostFocus:
                    _isActive = false;
                    std::cout << "Lost focus" << std::endl;
                    notify(Type::WINDOW_LOST_FOCUS);
                    break;

                case sf::Event::GainedFocus:
                    _isActive = true;
                    std::cout << "Gained focus" << std::endl;
                    notify(Type::WINDOW_GAINED_FOCUS);
                    break;

                case sf::Event::Resized:
                    notify(std::shared_ptr<Event>(
                            new WindowResizeEvent(event.size.width, event.size.height)
                    ));
                    break;

                default:
                    break;
            }
        }
    }

    void GameWindow::onNotify(engine::events::Type type) {
        if (type == engine::events::Type::CLOSE)
            _win->close();
    }

    void GameWindow::onNotify(engine::events::Event *event) {
        if (event->type == engine::events::Type::WINDOW_MOVE) {
            auto *moveEvent = dynamic_cast<engine::events::WindowMoveEvent *>(event);
            _win->setPosition(_win->getPosition() + moveEvent->move);
        }
    }
}
