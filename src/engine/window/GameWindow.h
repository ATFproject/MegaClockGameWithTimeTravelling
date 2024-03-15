//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H

#include "observers/Subject.h"
#include "game/Game.h"
#include "components/ComponentInterface.h"
#include "Events.h"

namespace window {
    class GameWindow : public engine::Subject, public engine::Observer {
    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window);
        void startRendering();

        void onNotify(const engine::events::Event &event) override;

        engine::game::GameObject *addGameObject(engine::components::InputComponent *ic,
                                                engine::components::PhysicsComponent *pc,
                                                engine::components::GraphicsComponent *gc);

        void removeGameObject(engine::game::GameObject *obj);

        void addWorld(b2World *world);

        tgui::Gui &getGui();

    private:
        sf::RenderWindow *_win;
        tgui::Gui _gui;

        engine::game::Game _game;
        bool _isActive;

        void _handleSfmlEvents();
    };

    struct WindowCloseEvent : public engine::events::Event {

    };

    struct WindowResizeEvent : public engine::events::Event {
        const sf::Vector2u newSize;
        explicit WindowResizeEvent(uint x, uint y) : newSize(sf::Vector2u(x, y)) {}
    };

    struct WindowMoveEvent : public engine::events::Event {
        const sf::Vector2i move;
        explicit WindowMoveEvent(int x, int y) : move(sf::Vector2i(x, y)) {}
    };

    struct WindowFocusChangeEvent : public engine::events::Event {
        bool inFocus;
        explicit WindowFocusChangeEvent(bool inFocus) : inFocus(inFocus) {}
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
