//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "GameDef.h"
#include "observers/Observer.h"

namespace engine::game {
    class Game : public events::Observer {
    public:
        Game() = default;

        void operator<<(GameObject *toAdd);
        void tick();
        void resize(sf::Vector2u size);

        using events::Observer::onNotify;
        void onNotify(events::Event *event) override;
    private:
        std::vector<GameObject *> _gameObjects;
        sf::Clock _timer;
    };
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
