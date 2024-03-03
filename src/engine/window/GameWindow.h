//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H

#include "observers/Subject.h"
#include "game/Game.h"
#include "components/ComponentInterface.h"

namespace window {
    class GameWindow : public engine::Subject, public engine::Observer {
    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window);
        void startRendering();

        void onNotify(const events::Event &event) override;

        void addGameObject(engine::components::InputComponent *ic,
                           engine::components::PhysicsComponent *pc,
                           engine::components::GraphicsComponent *gc);

    private:
        sf::RenderWindow *_win;
        engine::game::Game _game;
        bool _isActive;

        void _handleSfmlEvents();
    };

    struct WindowCloseEvent : public events::Event {

    };

    struct WindowResizeEvent : public events::Event {
        const sf::Vector2u newSize;
        explicit WindowResizeEvent(uint x, uint y) : newSize(sf::Vector2u(x, y)) {}
    };

    struct WindowMoveEvent : public events::Event {
        const sf::Vector2i move;
        explicit WindowMoveEvent(int x, int y) : move(sf::Vector2i(x, y)) {}
    };

    struct WindowFocusChangeEvent : public events::Event {
        bool inFocus;
        explicit WindowFocusChangeEvent(bool inFocus) : inFocus(inFocus) {}
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
