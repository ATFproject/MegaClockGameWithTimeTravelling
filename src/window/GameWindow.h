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
    class GameWindow : public game::events::Subject, public game::events::Observer {
    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window);
        void startRendering();

        void onNotify(game::events::GameEventType type) override;
        void onNotify(game::events::GameEvent *event) override;

    private:
        sf::RenderWindow *_win;
        game::Game _game;
        game::Keyboard keyboard;
        bool _isActive;

        void _handleSfmlEvents();
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
