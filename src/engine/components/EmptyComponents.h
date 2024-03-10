//
// Created by livefish on 2/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H

#include "ComponentInterface.h"

namespace engine::components {
    class EmptyGraphicsComponent : public GraphicsComponent {
    public:
        void draw(game::GameObject *gameObject) override {};
    };

    class EmptyInputComponent : public InputComponent {
    public:
        void tick(game::GameObject *gameObject, game::Game &game) override {}
    };

    class EmptyPhysicsComponent : public PhysicsComponent {
    public:
        void tick(game::GameObject *gameObject, game::Game &game) override {}
    };
}
#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_EMPTYCOMPONENTS_H
