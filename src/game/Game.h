//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "GameDef.h"

#include "GameObject.h"
#include "SFML/System/Clock.hpp"

namespace game {
    class Game {
    public:
        Game() = default;

        void operator<<(GameObject *toAdd) {
            _gameObjects.push_back(toAdd);
        }

        void tick() {
            sf::Time elapsed = _timer.getElapsedTime();

            for (GameObject *gameObject : _gameObjects) {
                gameObject->tick(elapsed, *this);
            }

            for (GameObject *gameObject : _gameObjects) {
                gameObject->draw();
            }
            _timer.restart();
        }

        void resize(unsigned int w, unsigned int h) {
            std::cout << "Test game size output! " << w << ", " << h << std::endl;
            // TODO: Convert this to graphics component and use it
        }

    private:
        sf::Clock _timer;
        std::vector<GameObject *> _gameObjects;
    };

} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
