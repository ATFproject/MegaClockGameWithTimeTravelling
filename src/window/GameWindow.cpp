//
// Created by livefish on 2/19/24.
//

#include "GameWindow.h"
#include "game/components/Demo components/GameComponent.h"
#include "components/WindowControlComponent.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _win(window), _isActive(false) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
        auto *window_control = new game::GameObject();
        window_control->setInput(new game::components::GameComponent(this));

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

        using namespace game::events;

        while (_win->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    _win->close();
                    break;

                case sf::Event::LostFocus:
                    _isActive = false;
                    std::cout << "Lost focus" << std::endl;
                    notify(GameEventType::WINDOW_LOST_FOCUS);
                    break;

                case sf::Event::GainedFocus:
                    _isActive = true;
                    std::cout << "Gained focus" << std::endl;
                    notify(GameEventType::WINDOW_GAINED_FOCUS);
                    break;

                case sf::Event::Resized:
                    notify(std::shared_ptr<GameEvent>(
                            new WindowResizeEvent(event.size.width, event.size.height)
                    ));
                    break;

                default:
                    break;
            }
        }
    }

    void GameWindow::onNotify(game::events::GameEventType type) {
        if (type == game::events::GameEventType::CLOSE)
            _win->close();
    }

    void GameWindow::onNotify(game::events::GameEvent *event) {
        if (event->type == game::events::GameEventType::WINDOW_MOVE) {
            auto *moveEvent = dynamic_cast<game::events::WindowMoveEvent *>(event);
            _win->setPosition(_win->getPosition() + moveEvent->move);
        }
    }
}
