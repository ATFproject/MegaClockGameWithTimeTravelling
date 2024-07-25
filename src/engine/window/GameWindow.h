// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H

#include "game/GameObject.h"
#include "game/GameProperties.h"

namespace window {
    class GameWindow : public engine::Observer, public engine::Subject {
    public:
        GameWindow() = delete;

        explicit GameWindow(sf::RenderWindow *window);

        engine::game::GameProperties getProperties() const;
        void setProperties(const engine::game::GameProperties &newProps);

        void startRendering();

        void onNotify(const engine::Event &event) override;

        engine::game::GameObject *addGameObject(engine::components::InputComponent *ic,
                                                engine::components::PhysicsComponent *pc,
                                                engine::components::GraphicsComponent *gc);

        void removeGameObject(engine::game::GameObject *obj);

        tgui::Gui &getGui();

    private:
        void handleSfmlEvents();

    private:
        bool _isActive;

        sf::RenderWindow *_win;
        tgui::Gui _gui;
        engine::game::Game _game;
        engine::game::GameProperties _gameProperties{};
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
