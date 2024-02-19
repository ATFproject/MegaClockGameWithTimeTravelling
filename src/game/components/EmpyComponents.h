//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_EMPYCOMPONENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_EMPYCOMPONENTS_H

#include <SFML/System/Time.hpp>
#include "ComponentInterface.h"

namespace game::components {
    class EmptyGraphicsComponent : public GraphicsComponent {
    public:
        void draw(GameObject *gameObject) override {};
    };

    class EmptyInputComponent : public InputComponent {
    public:
        void tick(GameObject *gameObject, Game &game) override {}
    };

    class EmptyPhysicsComponent : public PhysicsComponent {
    public:
        void tick(GameObject *gameObject, sf::Time dt, Game &game) override {}
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_EMPYCOMPONENTS_H
