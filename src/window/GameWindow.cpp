//
// Created by livefish on 2/19/24.
//

#include "GameWindow.h"
#include "components/WindowControlComponent.h"

namespace window {
    GameWindow::GameWindow(sf::RenderWindow *window) : _win(window), _isActive(false) {
        std::cout << "Window created!" << std::endl;
        addObserver(&_game);
        _game << new game::GameObject(new game::components::WindowControlComponent(this));
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

    void GameWindow::onNotify(game::events::GameEventType type) {
        if (type == game::events::GameEventType::CLOSE)
            _win->close();
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
                    notify(game::events::GameEventType::WINDOW_LOST_FOCUS);
                    break;

                case sf::Event::GainedFocus:
                    _isActive = true;
                    std::cout << "Gained focus" << std::endl;
                    notify(game::events::GameEventType::WINDOW_GAINED_FOCUS);
                    break;

                case sf::Event::Resized:
                    notify(std::shared_ptr<game::events::GameEvent>(
                            new game::events::WindowResizeEvent(event.size.width, event.size.height)
                    ));
                    break;

                default:
                    break;
            }
        }
    }
}
