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

        void addGameObject(engine::components::InputComponent *ic,
                           engine::components::PhysicsComponent *pc,
                           engine::components::GraphicsComponent *gc);

        tgui::Gui _gui;
    private:
        void handleSfmlEvents();

    private:
        bool _isActive;

        sf::RenderWindow *_win;
        engine::game::Game _game;
        engine::game::GameProperties _gameProperties{};
    };

    struct WindowCloseEvent : public engine::Event {
    };

    struct WindowResizeEvent : public engine::Event {
        const sf::Vector2u newSize;
        explicit WindowResizeEvent(uint x, uint y) : newSize(sf::Vector2u(x, y)) {}
    };

    struct WindowFocusChangeEvent : public engine::Event {
        bool inFocus;
        explicit WindowFocusChangeEvent(bool inFocus) : inFocus(inFocus) {}
    };

    struct WindowViewChangedEvent : public engine::Event {
        sf::View newView;
        explicit WindowViewChangedEvent(const sf::View &newView) : newView(newView) {}
    };

    struct KeyPressedEvent : public engine::Event {
        sf::Event::KeyEvent keyEvent;
        explicit KeyPressedEvent(const sf::Event::KeyEvent &keyEvent) : keyEvent(keyEvent) {}
    };

    struct KeyReleasedEvent : public engine::Event {
        sf::Event::KeyEvent keyEvent;
        explicit KeyReleasedEvent(const sf::Event::KeyEvent &keyEvent) : keyEvent(keyEvent) {}
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMEWINDOW_H
