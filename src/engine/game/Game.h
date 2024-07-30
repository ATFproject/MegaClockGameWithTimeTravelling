// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "observers/Subject.h"
#include "resources/Resources.h"

namespace engine::game {
    class GameObject;

    class Game : public Observer, public Subject {
    public:
        Game();

        void addGameObject(std::unique_ptr<GameObject>);
        void tick();
        void draw();

        bool isKeyPressed(const sf::Keyboard::Scancode k);
        bool wasKeyClicked(const sf::Keyboard::Scancode k);

        [[nodiscard]] sf::Vector2u getSize() const;

        void onNotify(const Event &event) override;

    public:
        std::optional<b2World> _world;

    private:
        std::vector<std::unique_ptr<GameObject>> _gameObjects;
        sf::Vector2u _size;
        std::unique_ptr<engine::ResourceHandler> _resourceHandler;

    private:
        bool _keys[256]{};
        bool _click[256]{};
        bool _keysOld[256]{};
    };

    struct GameResizeEvent : public Event {
        sf::Vector2u newSize;
        explicit GameResizeEvent(const sf::Vector2u &size) : newSize(size) {}
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
