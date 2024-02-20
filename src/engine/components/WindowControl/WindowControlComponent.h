//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H

namespace engine::components {
    class WindowControlComponent : public InputComponent, public events::Subject {
    public:
        explicit WindowControlComponent(window::GameWindow *win) {
            this->addObserver(win);
        }

        void tick([[maybe_unused]]GameObject *gameObject, Game &game) override {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                notify(engine::events::Type::CLOSE);
            }
        }
    };
}
// engine::components

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_WINDOWCONTROLCOMPONENT_H
