//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_PHYSICSCOMPONENT_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_PHYSICSCOMPONENT_H

#include "GameDef.h"
#include "SFML/System/Clock.hpp"

namespace game {
    class PhysicsComponent {
    public:
        virtual void tick(GameObject *gameObject, sf::Time dt, Game &game) = 0;
        virtual ~PhysicsComponent() = default;
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_PHYSICSCOMPONENT_H
