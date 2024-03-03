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

        void onNotifyType(events::Type type) override;
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


    struct WindowResizeEvent : public events::Event {
        const sf::Vector2u newSize;

        WindowResizeEvent(unsigned int w, unsigned int h) :
                Event(events::Type::WINDOW_RESIZED),
                newSize(sf::Vector2u(w, h)) {}
    };

    struct WindowMoveEvent : public events::Event {
        sf::Vector2i move;

        WindowMoveEvent(int x, int y) :
                Event(events::Type::WINDOW_MOVE), move(sf::Vector2i(x, y)) {}
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
