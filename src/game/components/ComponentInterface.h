//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H

#include "GameDef.h"

namespace game::components {
    class GraphicsComponent {
    public:
        virtual void draw(GameObject *gameObject) = 0;
        virtual ~GraphicsComponent() = default;
    };

    class InputComponent {
    public:
        virtual void tick(GameObject *gameObject, Game &game) = 0;
        virtual ~InputComponent() = default;
    };

    class PhysicsComponent {
    public:
        virtual void tick(GameObject *gameObject, sf::Time dt, Game &game) = 0;
        virtual ~PhysicsComponent() = default;
    };
}



#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
