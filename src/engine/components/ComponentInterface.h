//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H

#include "ComponentDef.h"
#include "game/GameDef.h"

namespace engine::components {
    class GraphicsComponent {
    public:
        virtual void draw(game::GameObject *gameObject) = 0;
        virtual ~GraphicsComponent() = default;
    };

    class InputComponent {
    public:
        virtual void tick(game::GameObject *gameObject, game::Game &game) = 0;
        virtual ~InputComponent() = default;
    };

    class PhysicsComponent {
    public:
        virtual void tick(game::GameObject *gameObject, sf::Time dt, game::Game &game) = 0;
        virtual ~PhysicsComponent() = default;
    };
}

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_COMPONENTINTERFACE_H
