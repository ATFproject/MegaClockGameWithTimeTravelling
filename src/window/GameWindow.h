//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H

#include <memory>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "Game.h"

#include "Keyboard.h"
#include "game/observers/Subject.h"

namespace window {
    class GameWindow : public game::events::Subject {
    private:
        sf::RenderWindow *_win;
        game::Game _game;
        game::Keyboard keyboard;
        bool _isActive;

        void _handleNewEvents() {
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
                        std::cout << "Resized: " << event.size.width << ", " << event.size.height << std::endl;
                        notify(std::shared_ptr<game::events::GameEvent>(
                                new game::events::WindowResizeEvent(event.size.width, event.size.height)
                        ));
                        break;

                    case sf::Event::KeyPressed:
                        keyboard._keys[event.key.scancode] = true;
                        break;

                    case sf::Event::KeyReleased:
                        keyboard._keys[event.key.scancode] = false;
                        break;

                    default:
                        break;
                }
            }
        }

    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window) : _win(window), _isActive(false) {
            std::cout << "Window created!" << std::endl;
        };

        void startRendering() {
            _isActive = true;
            while (_win->isOpen()) {
                _handleNewEvents();

                if (_isActive) {
                    _game.tick();
                }

                _win->display();
            }
        }
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
