//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H

#include "observers/Subject.h"
#include "game/Game.h"

namespace window {
    class GameWindow : public engine::events::Subject, public engine::events::Observer {
    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window);
        void startRendering();

        void onNotify(engine::events::Type type) override;
        void onNotify(engine::events::Event *event) override;

    private:
        sf::RenderWindow *_win;
        engine::game::Game _game;
        bool _isActive;

        void _handleSfmlEvents();
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
