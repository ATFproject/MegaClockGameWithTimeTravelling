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
        Game();

        void operator<<(GameObject *toAdd) {
            gameObjects.push_back(toAdd);
        }

        void start() {
            while (true) {
                sf::Time elapsed = timer.getElapsedTime();

                // TODO: update keyboard

                for (GameObject *gameObject : gameObjects) {
                    gameObject->tick(elapsed, *this);
                }

                for (GameObject *gameObject : gameObjects) {
                    gameObject->draw();
                }
                timer.restart();
            }
        }

    private:
        sf::Clock timer;
        std::vector<GameObject *> gameObjects;
    };

} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
