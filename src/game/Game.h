//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H

#include "observers/Observer.h"
#include "GameObject.h"

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

        using events::Observer::onNotify;
        void onNotify(events::GameEvent *event) override {
            std::cout << "Game received event: " + events::getTypeString(event->type) << std::endl;

            switch (event->type) {
                case events::GameEventType::WINDOW_RESIZED: {
                    auto *resizeEvent = dynamic_cast<events::WindowResizeEvent *>(event);
                    resize(resizeEvent->newSize);
                    break;
                }
                default:
                    break;
            }
        }

        std::vector<GameObject *> _gameObjects;
    private:
        sf::Clock _timer;
    };

} // game

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAME_H
