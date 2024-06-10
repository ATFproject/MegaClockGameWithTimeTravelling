//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "GameDef.h"
#include "observers/Subject.h"

namespace engine::game {
    class Game : public Observer, public Subject {
    public:
        std::optional<b2World> _world;

        Game() = default;

        void operator<<(GameObject *toAdd);
        void removeGameObject(GameObject *toRemove);
        void tick();
        void draw();

        bool isKeyPressed(const sf::Keyboard::Scancode k);
        bool wasKeyClicked(const sf::Keyboard::Scancode k);

        [[nodiscard]] sf::Vector2u getSize() const;

        void onNotify(const Event &event) override;
        ~Game() override;

    private:
        std::vector<GameObject *> _gameObjects;
        std::vector<GameObject *> _gameObjectsToDelete;
        sf::Vector2u _size;

        bool _keys[256]{};
        bool _click[256]{};
        bool _keysOld[256]{};
    };

    struct GameResizeEvent : public Event {
        sf::Vector2u _newSize;
        explicit GameResizeEvent(const sf::Vector2u &size) : _newSize(size) {}
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
