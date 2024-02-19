//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H

#include "ComponentInterface.h"
#include "observers/Subject.h"

#include "GameWindow.h"

namespace game::components {
    class WindowControlComponent : public InputComponent, public events::Subject {
    public:
        explicit WindowControlComponent(window::GameWindow *win) {
            this->addObserver(win);
        }

        void tick([[maybe_unused]]GameObject *gameObject, Game &game) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                notify(game::events::GameEventType::CLOSE);
            }
        }
    };
}
// game::components

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H
