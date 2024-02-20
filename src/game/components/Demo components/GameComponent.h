//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H

#include "game/components/ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace game::components {
    class GameComponent : public InputComponent, public events::Subject {
    public:
        explicit GameComponent(window::GameWindow *win) {
            this->addObserver(win);
        }

        void tick([[maybe_unused]]GameObject *gameObject, Game &game) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                notify(std::shared_ptr<events::GameEvent>(
                        new events::WindowMoveEvent(10, 0)
                ));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                notify(std::shared_ptr<events::GameEvent>(
                        new events::WindowMoveEvent(-10, 0)
                ));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                notify(std::shared_ptr<game::events::GameEvent>(
                        new events::WindowMoveEvent(0, -10)
                ));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                notify(std::shared_ptr<events::GameEvent>(
                        new events::WindowMoveEvent(0, 10)
                ));
            }

        }
    };
}
// game::components
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_GAMECOMPONENT_H
