//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "GameDef.h"

#include "GameObject.h"
#include "observers/Observer.h"
#include "SFML/System/Clock.hpp"

namespace game {
    class Game : public events::Observer {
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

        void resize(sf::Vector2u size) {
            std::cout << "Test game size output! " << size.x << ", " << size.y << std::endl;
            // TODO: Convert this to graphics component and use it
        }

        void onNotify(events::GameEventType type) override {
            std::cout << "Game received event: " + events::getTypeString(type) << std::endl;
        }

        void onNotify(events::GameEvent *event) override {
            switch (event->type) {
                case events::GameEventType::WINDOW_RESIZED: {
                    auto *resizeEvent = dynamic_cast<events::WindowResizeEvent *>(event);
                    resize(resizeEvent->newSize);
                    break;
                }
                case events::GameEventType::WINDOW_LOST_FOCUS:
                case events::GameEventType::WINDOW_GAINED_FOCUS:
                    break;
            }
        }

    private:
        sf::Clock _timer;
        std::vector<GameObject *> _gameObjects;
    };

} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
