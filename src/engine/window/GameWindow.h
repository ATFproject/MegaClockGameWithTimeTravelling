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

        void onNotify(const engine::Event &event) override;

        engine::game::GameObject *addGameObject(engine::components::InputComponent *ic,
                                                engine::components::PhysicsComponent *pc,
                                                engine::components::GraphicsComponent *gc);

        void removeGameObject(engine::game::GameObject *obj);

        tgui::Gui &getGui();

    private:
        sf::RenderWindow *_win;
        tgui::Gui _gui;

        engine::game::Game _game;
        bool _isActive;

        void handleSfmlEvents();
    };

    struct WindowCloseEvent : public engine::Event {
    };

    struct WindowResizeEvent : public engine::Event {
        const sf::Vector2u _newSize;
        explicit WindowResizeEvent(uint x, uint y) : _newSize(sf::Vector2u(x, y)) {}
    };

    struct WindowFocusChangeEvent : public engine::Event {
        bool _inFocus;
        explicit WindowFocusChangeEvent(bool inFocus) : _inFocus(inFocus) {}
    };

    struct WindowViewChangedEvent : public engine::Event {
        sf::View _newView;
        explicit WindowViewChangedEvent(const sf::View &newView) : _newView(newView) {}
    };

    struct KeyPressedEvent : public engine::Event {
        sf::Event::KeyEvent _keyEvent;
        explicit KeyPressedEvent(const sf::Event::KeyEvent &keyEvent) : _keyEvent(keyEvent) {}
    };

    struct KeyReleasedEvent : public engine::Event {
        sf::Event::KeyEvent _keyEvent;
        explicit KeyReleasedEvent(const sf::Event::KeyEvent &keyEvent) : _keyEvent(keyEvent) {}
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
